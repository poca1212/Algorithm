import pygame
import sys
import random
import math
from collections import deque

# 초기화
pygame.init()
WIDTH, HEIGHT = 1000, 800
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Survival Defense - Pygame")
FPS = 60
CLOCK = pygame.time.Clock()

# 맵 크기
MAP_WIDTH, MAP_HEIGHT = 2000, 1600

# 폰트 설정
try:
    FONT = pygame.font.SysFont('malgungothic', 24)
    BIGFONT = pygame.font.SysFont('malgungothic', 40)
    SMALLFONT = pygame.font.SysFont('malgungothic', 18)
except:
    FONT = pygame.font.SysFont(None, 24)
    BIGFONT = pygame.font.SysFont(None, 40)
    SMALLFONT = pygame.font.SysFont(None, 18)

# 색
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (220,60,60)
GREEN = (40, 180, 99)
BLUE = (80,150,240)
YELLOW = (240,220,80)
GRAY = (120,120,120)
PURPLE = (140,0,140)
GRASS_COLOR = (30, 120, 60)

# 플레이어 설정/스탯
BASE_PLAYER_SPEED = 4.5 # 이동 속도 증가
PLAYER_SIZE = 28
STARTING_STR = 8

# 무기 정의
WEAPONS = {
    1: { # 기관총 (고정)
        'name': 'Light MG',
        'fire_delay': 12,      # 연사 속도 느리게 (프레임 단위)
        'bullet_speed': 10,
        'mag': 150,
        'reload_time': 180, # 3초 (FPS * 3)
        'move_penalty': 0.7,
    }
}

# 몬스터 타입
MONSTER_TYPES = {
    1: {'name':'Grunt', 'base_hp':20, 'base_speed':1.0, 'damage':1, 'exp': 8},
    2: {'name':'Brute', 'base_hp':40, 'base_speed':1.1, 'damage':1, 'exp': 18},
    3: {'name':'Boss', 'base_hp':300, 'base_speed':0.9, 'damage':1, 'exp': 130}
}

# 상점 아이템 (요구사항에 맞춰 비용 수정)
SHOP_ITEMS = {
    'atk_boost': {'name':'공격력 부스트', 'cost':10, 'desc':'15초간 공격력 +6 (중첩 가능)'},
    'add_gun': {'name':'총 개수 늘리기', 'cost':20, 'desc':'공격하는 총의 개수를 늘립니다.'}
}

# 게임 상태
STATE_LOBBY = 'lobby'
STATE_PLAYING = 'playing'
STATE_INTERMISSION = 'intermission'  # (불필요하지만 여전히 정의)

# 유틸 함수
def draw_text(surf, text, x, y, font=FONT, color=WHITE, center=False):
    img = font.render(text, True, color)
    rect = img.get_rect()
    if center:
        rect.center = (x, y)
    else:
        rect.topleft = (x, y)
    surf.blit(img, rect)

def clamp(v,a,b):
    return max(a,min(b,v))

# 클래스 정의
class Player:
    def __init__(self):
        self.x = MAP_WIDTH // 2
        self.y = MAP_HEIGHT // 2
        self.size = PLAYER_SIZE
        self.base_speed = BASE_PLAYER_SPEED
        self.strength = STARTING_STR
        self.level = 1
        self.exp = 0
        self.exp_to_level = 50
        self.gems = 10
        self.stat_points = 0
        self.weapon_id = 1 # Light MG로 고정
        self.fire_cool = 0
        self.mag = WEAPONS[self.weapon_id]['mag']
        self.reloading = 0
        self.items_active = {'atk_boost':0}
        self.num_guns = 1
        self.aim_angle = 0

    @property
    def speed(self):
        s = self.base_speed
        if self.weapon_id:
            s *= WEAPONS[self.weapon_id]['move_penalty']
        return clamp(s, 0.8, 8)

    @property
    def damage(self):
        base = self.strength
        if self.items_active['atk_boost'] > 0:
            base += 6
        return base

    def give_exp(self, e):
        self.exp += e
        while self.exp >= self.exp_to_level:
            self.exp -= self.exp_to_level
            self.level += 1
            self.strength += 1
            self.exp_to_level = int(self.exp_to_level * 1.4)

    def update_items(self):
        for k in list(self.items_active.keys()):
            if self.items_active[k] > 0:
                self.items_active[k] -= 1

    def reload_weapon(self):
        if self.weapon_id is None or self.reloading > 0: return
        w = WEAPONS[self.weapon_id]
        self.reloading = w['reload_time']

    def fire(self):
        if self.reloading > 0 or self.fire_cool > 0:
            return False
        if self.mag <= 0:
            self.reload_weapon()
            return False
        w = WEAPONS[self.weapon_id]
        self.fire_cool = w['fire_delay']
        self.mag -= 1
        return True

    def update(self):
        if self.fire_cool > 0:
            self.fire_cool -= 1
        if self.reloading > 0:
            self.reloading -= 1
            if self.reloading == 0:
                self.mag = WEAPONS[self.weapon_id]['mag']
        self.update_items()

    def draw(self, surf, camera):
        # 플레이어 몸통
        body_x, body_y = self.x - camera.x, self.y - camera.y
        head_r = self.size // 2
        pygame.draw.circle(surf, BLUE, (int(body_x), int(body_y - head_r)), head_r)
        pygame.draw.line(surf, BLUE, (int(body_x), int(body_y - head_r//2)), (int(body_x), int(body_y + self.size)), 4)
        
        # 조준선
        indicator_len = 25
        end_x = body_x + indicator_len * math.cos(self.aim_angle)
        end_y = body_y + indicator_len * math.sin(self.aim_angle)
        pygame.draw.line(surf, RED, (body_x, body_y), (end_x, end_y), 3)

class Bullet:
    def __init__(self, x, y, vx, vy, dmg):
        self.x, self.y = x, y
        self.vx, self.vy = vx, vy
        self.r, self.dmg = 4, dmg
        self.life = 120

    def update(self):
        self.x += self.vx
        self.y += self.vy
        self.life -= 1

    def draw(self, surf, camera):
        pygame.draw.circle(surf, YELLOW, (int(self.x - camera.x), int(self.y - camera.y)), self.r)

class Gem:
    def __init__(self, x, y):
        self.x, self.y = x, y
        self.size = 8
        self.life = 600 # 10초

    def update(self):
        self.life -= 1

    def draw(self, surf, camera):
        pygame.draw.rect(surf, YELLOW, (self.x - self.size//2 - camera.x, self.y - self.size//2 - camera.y, self.size, self.size))

class Monster:
    def __init__(self, mtype, x, y, hp, speed, damage):
        self.type = mtype
        self.x, self.y = x, y
        self.max_hp, self.hp = hp, hp
        self.speed, self.damage = speed, damage
        
        # 체력에 따라 크기와 색 결정
        size_bonus = min(20, self.max_hp / 20)
        self.size = 20 + size_bonus
        
        red_intensity = min(255, 50 + self.max_hp)
        self.color = (red_intensity, 50, 50)


    def update(self, target_x, target_y):
        dx, dy = target_x - self.x, target_y - self.y
        dist = math.hypot(dx,dy)
        if dist > 0:
            self.x += (dx / dist) * self.speed
            self.y += (dy / dist) * self.speed

    def draw(self, surf, camera):
        pygame.draw.rect(surf, self.color, (self.x - self.size//2 - camera.x, self.y - self.size//2 - camera.y, self.size, self.size))
        # HP Bar
        if self.hp < self.max_hp:
            ratio = self.hp / self.max_hp
            bar_y = self.y - self.size//2 - 8 - camera.y
            pygame.draw.rect(surf, BLACK, (self.x-self.size//2 - camera.x, bar_y, self.size, 6))
            pygame.draw.rect(surf, GREEN, (self.x-self.size//2- camera.x, bar_y, int(self.size*ratio), 6))

class Camera:
    def __init__(self):
        self.x = 0
        self.y = 0

    def update(self, target):
        self.x = target.x - WIDTH // 2
        self.y = target.y - HEIGHT // 2
        self.x = clamp(self.x, 0, MAP_WIDTH - WIDTH)
        self.y = clamp(self.y, 0, MAP_HEIGHT - HEIGHT)

class Game:
    def __init__(self):
        self.state = STATE_LOBBY
        self.player = Player()
        self.camera = Camera()
        self.bullets = []
        self.monsters = []
        self.gems = []
        self.wave = 0
        self.interm_time = 0
        self.spawn_queue = deque()
        self.shop_open = False
        self.wave_clear_timer = 0
        # shop rects (화면 고정 위치)
        self.shop_item_rects = {
            'atk_boost': pygame.Rect(50, 200, 280, 80),
            'add_gun': pygame.Rect(50, 300, 280, 80),
        }
        self.next_wave_rect = pygame.Rect(WIDTH - 220, 20, 200, 50)

    def start_wave(self):
        self.wave += 1
        self.monsters.clear()
        self.bullets.clear()
        self.spawn_queue.clear()
        self.wave_clear_timer = 0
        base_count = 5 + self.wave * 2
        spawn_list = []
        for _ in range(base_count):
            t = 1 if random.random() < 0.7 else 2
            spawn_list.append(t)
        if self.wave % 10 == 0 and self.wave > 0:
            for _ in range(self.wave // 10):
                spawn_list.append(3)
        for t in spawn_list:
            m_info = MONSTER_TYPES[t]
            hp = int(m_info['base_hp'] * (1 + self.wave * 0.25))
            speed = m_info['base_speed'] * (1 + (self.wave - 1) * 0.03)
            # 맵 밖에서 스폰
            angle = random.uniform(0, 2 * math.pi)
            spawn_dist = max(WIDTH, HEIGHT)
            x = self.player.x + spawn_dist * math.cos(angle)
            y = self.player.y + spawn_dist * math.sin(angle)
            self.spawn_queue.append((t, x, y, hp, max(0.4, speed), m_info['damage']))
        self.state = STATE_PLAYING

    def spawn_from_queue(self):
        if self.spawn_queue and random.random() < 0.05:
             t,x,y,hp,speed,dmg = self.spawn_queue.popleft()
             self.monsters.append(Monster(t,x,y,hp,speed,dmg))

    def update(self):
        if self.state == STATE_PLAYING:
            self.player.update()
            self.camera.update(self.player)
            self.spawn_from_queue()

            for b in self.bullets[:]:
                b.update()
                if b.life <= 0: self.bullets.remove(b)

            for m in self.monsters[:]:
                m.update(self.player.x, self.player.y)
                if math.hypot(m.x - self.player.x, m.y - self.player.y) < self.player.size:
                    self.reset_game()
                    return

            for g in self.gems[:]:
                g.update()
                if g.life <= 0: self.gems.remove(g)
                elif math.hypot(g.x - self.player.x, g.y - self.player.y) < self.player.size + 20:
                    self.player.gems += 1
                    self.gems.remove(g)

            for b in self.bullets[:]:
                for m in self.monsters[:]:
                    if math.hypot(b.x-m.x, b.y-m.y) < (b.r + m.size/2):
                        m.hp -= b.dmg
                        if b in self.bullets: self.bullets.remove(b)
                        if m.hp <= 0:
                            self.player.give_exp(MONSTER_TYPES[m.type]['exp'])
                            if random.random() < 0.20:
                                self.gems.append(Gem(m.x, m.y))
                            if m in self.monsters: self.monsters.remove(m)
                        break

            # 웨이브 클리어 처리: 몬스터와 스폰큐가 비었을 때 6초간 "Wave Clear!"를 보여주고 자동으로 다음 웨이브 시작
            if not self.spawn_queue and not self.monsters:
                if self.wave_clear_timer == 0:
                    self.wave_clear_timer = 6 * FPS
                    self.player.stat_points += 1
                else:
                    self.wave_clear_timer -= 1
                    if self.wave_clear_timer <= 0:
                        self.start_wave()

        elif self.state == STATE_INTERMISSION:
            # 이전 코드의 인터미션 루틴은 사용하지 않지만, 안전하게 대기
            self.interm_time -= 1
            if self.interm_time <= 0:
                self.start_wave()

    def reset_game(self):
        self.__init__()

    def shoot(self):
        if self.player.fire():
            w = WEAPONS[self.player.weapon_id]
            bs = w['bullet_speed']
            # 멀티샷 로직
            angles = [self.player.aim_angle]
            additional_angles = [
                self.player.aim_angle + math.pi, # 반대
                -math.pi/2, # 위
                math.pi/2,  # 아래
                self.player.aim_angle + math.pi/4, # 우하 대각
                self.player.aim_angle - math.pi/4, # 우상 대각
                self.player.aim_angle + 3*math.pi/4, # 좌하 대각
                self.player.aim_angle - 3*math.pi/4, # 좌상 대각
            ]
            for i in range(self.player.num_guns - 1):
                if i < len(additional_angles):
                    angles.append(additional_angles[i])
            for angle in angles:
                vx = math.cos(angle) * bs
                vy = math.sin(angle) * bs
                b = Bullet(self.player.x, self.player.y, vx, vy, self.player.damage)
                self.bullets.append(b)

    def handle_shop_click(self, pos):
        # 화면 고정 상점에서 클릭 처리
        if self.shop_item_rects['atk_boost'].collidepoint(pos) and self.player.gems >= SHOP_ITEMS['atk_boost']['cost']:
            self.player.gems -= SHOP_ITEMS['atk_boost']['cost']
            self.player.items_active['atk_boost'] += 15 * FPS
        if self.shop_item_rects['add_gun'].collidepoint(pos) and self.player.gems >= SHOP_ITEMS['add_gun']['cost'] and self.player.num_guns < 7:
            self.player.gems -= SHOP_ITEMS['add_gun']['cost']
            self.player.num_guns += 1

    def draw_shop(self, surf):
        # 반투명 배경
        s = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
        s.fill((10,10,20,180))
        surf.blit(s, (0,0))

        draw_text(surf, "[ 상점 ]", 180, 150, FONT, center=True)
        for item_key, rect in self.shop_item_rects.items():
            item = SHOP_ITEMS[item_key]
            pygame.draw.rect(surf, (40,40,60), rect, border_radius=5)
            if item_key == 'add_gun':
                gun_text = f" ({self.player.num_guns}/7)" if self.player.num_guns < 7 else " (MAX)"
                draw_text(surf, f"{item['name']}{gun_text}", rect.x + 15, rect.y + 10, color=WHITE)
            else:
                draw_text(surf, f"{item['name']} (보석 {item['cost']}개)", rect.x + 15, rect.y + 10)
            draw_text(surf, item['desc'], rect.x + 15, rect.y + 40, SMALLFONT)

        # 현재 보유 보석 등 정보
        draw_text(surf, f"보유 보석: {self.player.gems}", 50, 150)
        # 닫기 안내
        draw_text(surf, "TAB으로 상점 닫기", WIDTH - 220, HEIGHT - 40)

    def draw_ui(self, surf):
        draw_text(surf, f"웨이브: {self.wave}", 10, 10)
        draw_text(surf, f"보석: {self.player.gems}", 10, 35)
        draw_text(surf, f"레벨: {self.player.level} (EXP {self.player.exp}/{self.player.exp_to_level})", 10, 60)
        w_name = WEAPONS[self.player.weapon_id]['name']
        mag_status = "재장전중..." if self.player.reloading > 0 else str(self.player.mag)
        draw_text(surf, f"무기: {w_name} | 탄약: {mag_status}", 10, 85)
        if self.player.items_active['atk_boost'] > 0:
            draw_text(surf, f"공격력 부스트! ({self.player.items_active['atk_boost']/FPS:.1f}s)", WIDTH-250, 10, color=RED)
        if self.wave_clear_timer > 0:
            # 화면 중앙에 Wave Clear 메시지
            draw_text(surf, "Wave Clear!", WIDTH//2, HEIGHT//2 - 30, BIGFONT, center=True, color=YELLOW)
            draw_text(surf, f"다음 웨이브까지: {self.wave_clear_timer/FPS:.1f}s", WIDTH//2, HEIGHT//2 + 10, FONT, center=True)

    def draw(self, surf):
        surf.fill(GRASS_COLOR)
        self.player.draw(surf, self.camera)
        for g in self.gems: g.draw(surf, self.camera)
        for b in self.bullets: b.draw(surf, self.camera)
        for m in self.monsters: m.draw(surf, self.camera)
        self.draw_ui(surf)
        if self.shop_open:
            self.draw_shop(surf)


def intermission_screen(win, game):
    # 기존 코드와 호환성을 위해 남겨두었으나, 현재 게임은 자동 웨이브 시작/상점 오버레이를 사용합니다.
    item_rects = {
        'atk_boost': pygame.Rect(50, 200, 280, 80),
        'add_gun': pygame.Rect(50, 300, 280, 80),
    }
    stat_rects = {'str': pygame.Rect(800, 220, 40, 40)}
    next_wave_rect = pygame.Rect(WIDTH - 220, 20, 200, 50)

    while game.state == STATE_INTERMISSION:
        CLOCK.tick(FPS)
        for ev in pygame.event.get():
            if ev.type == pygame.QUIT: pygame.quit(), sys.exit()
            if ev.type == pygame.MOUSEBUTTONDOWN:
                pos = ev.pos
                if item_rects['atk_boost'].collidepoint(pos) and game.player.gems >= SHOP_ITEMS['atk_boost']['cost']:
                    game.player.gems -= SHOP_ITEMS['atk_boost']['cost']
                    game.player.items_active['atk_boost'] += 15 * FPS
                if item_rects['add_gun'].collidepoint(pos) and game.player.gems >= SHOP_ITEMS['add_gun']['cost'] and game.player.num_guns < 7:
                    game.player.gems -= SHOP_ITEMS['add_gun']['cost']
                    game.player.num_guns += 1
                if game.player.stat_points > 0 and stat_rects['str'].collidepoint(pos):
                    game.player.strength += 2
                    game.player.stat_points -= 1
                if next_wave_rect.collidepoint(pos):
                    game.interm_time = 0
        game.update()
        win.fill((10,10,20))
        draw_text(win, f"웨이브 {game.wave} 클리어!", WIDTH//2, 50, BIGFONT, center=True)
        draw_text(win, f"다음 웨이브까지: {game.interm_time/FPS:.1f}초", WIDTH//2, 100, FONT, center=True)
        draw_text(win, f"보유 보석: {game.player.gems}", 50, 150)
        pygame.draw.rect(win, (80,40,40), next_wave_rect)
        draw_text(win, "다음 웨이브", next_wave_rect.centerx, next_wave_rect.centery, FONT, center=True)
        draw_text(win, "[ 상점 ]", 180, 150, FONT, center=True)
        for item_key, rect in item_rects.items():
            item = SHOP_ITEMS[item_key]
            pygame.draw.rect(win, (40,40,60), rect, border_radius=5)
            if item_key == 'add_gun':
                gun_text = f" ({game.player.num_guns}/7)" if game.player.num_guns < 7 else " (MAX)"
                draw_text(win, f"{item['name']}{gun_text}", rect.x + 15, rect.y + 10)
            else:
                 draw_text(win, f"{item['name']} (보석 {item['cost']}개)", rect.x + 15, rect.y + 10)
            draw_text(win, item['desc'], rect.x + 15, rect.y + 40, SMALLFONT)
        draw_text(win, "[ 스탯 분배 ]", 670, 150, FONT, center=True)
        draw_text(win, f"사용 가능 포인트: {game.player.stat_points}", 550, 180)
        draw_text(win, f"힘 (+2): {game.player.strength}", 550, 230)
        if game.player.stat_points > 0:
            pygame.draw.rect(win, GREEN, stat_rects['str'], border_radius=5)
            draw_text(win, "+", stat_rects['str'].centerx, stat_rects['str'].centery, BIGFONT, center=True, color=BLACK)
        pygame.display.flip()


def main():
    game = Game()
    running = True
    mouse_down = False

    while running:
        CLOCK.tick(FPS)
        mouse_pos = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            # TAB으로 상점 열고 닫기
            if event.type == pygame.KEYDOWN and event.key == pygame.K_TAB:
                game.shop_open = not game.shop_open
            if game.state == STATE_LOBBY:
                if event.type == pygame.KEYDOWN or event.type == pygame.MOUSEBUTTONDOWN:
                    game.start_wave()
            elif game.state == STATE_PLAYING:
                if event.type == pygame.KEYDOWN and event.key == pygame.K_r:
                    game.player.reload_weapon()
                elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    mouse_down = True
                    # 상점이 열려있으면 클릭으로 구매 시도 (WASD 이동은 계속 가능)
                    if game.shop_open:
                        game.handle_shop_click(event.pos)
                elif event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    mouse_down = False

        if game.state == STATE_PLAYING:
            # 조준 각도 업데이트 (플레이어는 화면 중앙)
            player_screen_x, player_screen_y = WIDTH//2, HEIGHT//2
            game.player.aim_angle = math.atan2(mouse_pos[1] - player_screen_y, mouse_pos[0] - player_screen_x)

            keys = pygame.key.get_pressed()
            dx = (keys[pygame.K_d] or keys[pygame.K_RIGHT]) - (keys[pygame.K_a] or keys[pygame.K_LEFT])
            dy = (keys[pygame.K_s] or keys[pygame.K_DOWN]) - (keys[pygame.K_w] or keys[pygame.K_UP])
            if dx != 0 or dy != 0:
                mag = math.hypot(dx, dy)
                game.player.x += (dx/mag) * game.player.speed
                game.player.y += (dy/mag) * game.player.speed
                game.player.x = clamp(game.player.x, 0, MAP_WIDTH)
                game.player.y = clamp(game.player.y, 0, MAP_HEIGHT)

            if mouse_down:
                game.shoot()

        game.update()

        if game.state == STATE_LOBBY:
            WIN.fill((15,15,30))
            draw_text(WIN, '서바이벌 디펜스', WIDTH//2, HEIGHT//2 - 50, BIGFONT, center=True)
            draw_text(WIN, '아무 키나 눌러 시작', WIDTH//2, HEIGHT//2 + 20, FONT, center=True)
        elif game.state == STATE_PLAYING:
            game.draw(WIN)

        pygame.display.flip()

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()
