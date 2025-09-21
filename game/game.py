import pygame
import sys
import random

# ------------------------------
# Game Config
# ------------------------------
WIDTH, HEIGHT = 800, 800
FPS = 60
ARENA_PADDING = 60

PLAYER_SIZE = 42
BASE_SPEED = 3.2
BOOST_SPEED = 7.0
BOOST_DURATION_MS = 1500
BOOST_COOLDOWN_MS = 3000
SWORD_LENGTH = 34
SWORD_THICKNESS = 10
SWORD_DURATION_MS = 1000
ATTACK_COOLDOWN_MS = 1000
DAMAGE_PER_HIT = 10
DAMAGE_PER_HIT_BOOST = 15
START_HP = 50
HEAL_AMOUNT = 10

ITEM_SIZE = 24
ITEM_SPAWN_INTERVAL = 10000  # ms (10초)

# Colors
BG = (18, 18, 22)
ARENA_LINE = (70, 70, 80)
P1_COLOR = (80, 200, 255)
P2_COLOR = (255, 140, 100)
SWORD_COLOR = (240, 240, 80)
ITEM_COLOR = (120, 255, 120)
WHITE = (230, 230, 235)
RED = (230, 70, 70)
GREEN = (70, 210, 120)

# ------------------------------
# Classes
# ------------------------------
class Player:
    def __init__(self, pos, color, controls):
        self.color = color
        self.rect = pygame.Rect(pos[0], pos[1], PLAYER_SIZE, PLAYER_SIZE)
        self.facing = "down"
        self.base_speed = BASE_SPEED
        self.boost_speed = BOOST_SPEED
        self.controls = controls

        # Sword state
        self.sword_active = False
        self.sword_until = 0
        self.sword_has_hit = False

        # Combat state
        self.hp = START_HP
        self.last_attack_time = -ATTACK_COOLDOWN_MS

        # Boost state
        self.is_boosting = False
        self.boost_until = 0
        self.boost_cd_until = 0

        # Invincible state
        self.invincible = False
        self.invincible_until = 0
        self.visible = True
        self.last_blink = 0

    def current_speed(self, now_ms):
        if self.is_boosting and now_ms < self.boost_until:
            return self.boost_speed
        return self.base_speed

    def handle_input(self, keys, now_ms, arena_rect):
        dx = dy = 0
        if keys[self.controls["left"]]:
            dx -= 1
        if keys[self.controls["right"]]:
            dx += 1
        if keys[self.controls["up"]]:
            dy -= 1
        if keys[self.controls["down"]]:
            dy += 1

        if dx < 0:
            self.facing = "left"
        elif dx > 0:
            self.facing = "right"
        elif dy < 0:
            self.facing = "up"
        elif dy > 0:
            self.facing = "down"

        speed = self.current_speed(now_ms)
        self.rect.x += int(dx * speed)
        self.rect.y += int(dy * speed)
        self.rect.clamp_ip(arena_rect)

        # Boost activation
        if keys[self.controls["boost"]] and now_ms >= self.boost_cd_until:
            self.is_boosting = True
            self.boost_until = now_ms + BOOST_DURATION_MS
            self.boost_cd_until = now_ms + BOOST_DURATION_MS + BOOST_COOLDOWN_MS

        if self.is_boosting and now_ms >= self.boost_until:
            self.is_boosting = False

    def start_swing(self, now_ms):
        if not self.sword_active and now_ms - self.last_attack_time >= ATTACK_COOLDOWN_MS:
            self.sword_active = True
            self.sword_until = now_ms + SWORD_DURATION_MS
            self.sword_has_hit = False
            self.last_attack_time = now_ms

    def update(self, now_ms):
        # Sword 종료
        if self.sword_active and now_ms >= self.sword_until:
            self.sword_active = False
        # Invincible 종료
        if self.invincible and now_ms >= self.invincible_until:
            self.invincible = False
            self.visible = True
        # 깜빡임 처리
        if self.invincible:
            if now_ms - self.last_blink > 150:
                self.visible = not self.visible
                self.last_blink = now_ms

    def sword_rect(self):
        if not self.sword_active:
            return None
        x, y, w, h = self.rect
        if self.facing == "left":
            return pygame.Rect(x - SWORD_LENGTH, y + h // 2 - SWORD_THICKNESS // 2, SWORD_LENGTH, SWORD_THICKNESS)
        if self.facing == "right":
            return pygame.Rect(x + w, y + h // 2 - SWORD_THICKNESS // 2, SWORD_LENGTH, SWORD_THICKNESS)
        if self.facing == "up":
            return pygame.Rect(x + w // 2 - SWORD_THICKNESS // 2, y - SWORD_LENGTH, SWORD_THICKNESS, SWORD_LENGTH)
        if self.facing == "down":
            return pygame.Rect(x + w // 2 - SWORD_THICKNESS // 2, y + h, SWORD_THICKNESS, SWORD_LENGTH)
        return None

    def draw(self, surf):
        if self.visible:
            pygame.draw.rect(surf, self.color, self.rect, border_radius=8)
        eye_size = 6
        if self.facing == "left":
            eye = pygame.Rect(self.rect.left + 4, self.rect.centery - 3, eye_size, eye_size)
        elif self.facing == "right":
            eye = pygame.Rect(self.rect.right - 4 - eye_size, self.rect.centery - 3, eye_size, eye_size)
        elif self.facing == "up":
            eye = pygame.Rect(self.rect.centerx - 3, self.rect.top + 4, eye_size, eye_size)
        else:
            eye = pygame.Rect(self.rect.centerx - 3, self.rect.bottom - 4 - eye_size, eye_size, eye_size)
        pygame.draw.rect(surf, WHITE, eye, border_radius=3)

        if self.sword_active:
            srect = self.sword_rect()
            if srect:
                pygame.draw.rect(surf, SWORD_COLOR, srect, border_radius=4)


class Item:
    def __init__(self, pos):
        self.rect = pygame.Rect(pos[0], pos[1], ITEM_SIZE, ITEM_SIZE)

    def draw(self, surf):
        pygame.draw.rect(surf, ITEM_COLOR, self.rect, border_radius=6)


def draw_arena(surf, arena_rect):
    surf.fill(BG)
    pygame.draw.rect(surf, ARENA_LINE, arena_rect, width=4, border_radius=12)


def draw_hud(surf, p1, p2, font, now):
    bar_w = 280
    bar_h = 18

    # P1 HP
    p1_ratio = max(p1.hp, 0) / START_HP
    p1_back = pygame.Rect(ARENA_PADDING, 16, bar_w, bar_h)
    p1_hp = pygame.Rect(ARENA_PADDING, 16, int(bar_w * p1_ratio), bar_h)
    pygame.draw.rect(surf, (60,60,65), p1_back, border_radius=8)
    pygame.draw.rect(surf, GREEN if p1.hp>0 else RED, p1_hp, border_radius=8)
    txt1 = font.render(f"P1 HP: {p1.hp}", True, WHITE)
    surf.blit(txt1, (p1_back.left, p1_back.bottom + 4))

    if now < p1.boost_cd_until:
        cd_left = max(0,(p1.boost_cd_until - now)//1000)
        cd_txt = font.render(f"Boost CD: {cd_left}s", True, WHITE)
        surf.blit(cd_txt, (p1_back.left, p1_back.bottom + 24))

    # P2 HP
    p2_ratio = max(p2.hp,0)/START_HP
    p2_back = pygame.Rect(WIDTH-ARENA_PADDING-bar_w,16,bar_w,bar_h)
    p2_hp = pygame.Rect(WIDTH-ARENA_PADDING-bar_w,16,int(bar_w*p2_ratio),bar_h)
    pygame.draw.rect(surf,(60,60,65),p2_back,border_radius=8)
    pygame.draw.rect(surf, GREEN if p2.hp>0 else RED, p2_hp,border_radius=8)
    txt2 = font.render(f"P2 HP: {p2.hp}", True, WHITE)
    surf.blit(txt2, (p2_back.left, p2_back.bottom+4))
    if now < p2.boost_cd_until:
        cd_left = max(0,(p2.boost_cd_until - now)//1000)
        cd_txt = font.render(f"Boost CD: {cd_left}s", True, WHITE)
        surf.blit(cd_txt, (p2_back.left, p2_back.bottom + 24))


def check_sword_hit(attacker: Player, defender: Player, now_ms):
    if not attacker.sword_active or attacker.sword_has_hit or defender.invincible:
        return False
    srect = attacker.sword_rect()
    if srect and srect.colliderect(defender.rect):
        dmg = DAMAGE_PER_HIT_BOOST if attacker.is_boosting else DAMAGE_PER_HIT
        defender.hp -= dmg
        defender.invincible = True
        defender.invincible_until = now_ms + 1000
        defender.last_blink = now_ms
        attacker.sword_has_hit = True
        return True
    return False


def reset_round(p1, p2, arena_rect):
    p1.rect.topleft = (arena_rect.left + 80, arena_rect.centery - PLAYER_SIZE//2)
    p2.rect.topleft = (arena_rect.right - 80 - PLAYER_SIZE, arena_rect.centery - PLAYER_SIZE//2)
    p1.hp = START_HP
    p2.hp = START_HP
    p1.sword_active = p2.sword_active = False
    p1.is_boosting = p2.is_boosting = False
    p1.boost_cd_until = p2.boost_cd_until = 0
    p1.last_attack_time = p2.last_attack_time = 0


def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("2P Sword Arena")
    clock = pygame.time.Clock()
    font = pygame.font.SysFont("consolas",18)
    big_font = pygame.font.SysFont("consolas",32,bold=True)

    arena_rect = pygame.Rect(ARENA_PADDING, ARENA_PADDING, WIDTH-2*ARENA_PADDING, HEIGHT-2*ARENA_PADDING)

    p1_controls = {"up":pygame.K_w,"down":pygame.K_s,"left":pygame.K_a,"right":pygame.K_d,"swing":pygame.K_SPACE,"boost":pygame.K_f}
    p2_controls = {"up":pygame.K_UP,"down":pygame.K_DOWN,"left":pygame.K_LEFT,"right":pygame.K_RIGHT,"swing":pygame.K_KP0,"boost":pygame.K_KP_PERIOD}

    p1 = Player((arena_rect.left + 80, arena_rect.centery - PLAYER_SIZE//2), P1_COLOR, p1_controls)
    p2 = Player((arena_rect.right - 80 - PLAYER_SIZE, arena_rect.centery - PLAYER_SIZE//2), P2_COLOR, p2_controls)

    items = []
    last_item_spawn = pygame.time.get_ticks()

    running = True
    game_over = False

    while running:
        dt = clock.tick(FPS)
        now = pygame.time.get_ticks()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                if not game_over:
                    if event.key == p1.controls["swing"]:
                        p1.start_swing(now)
                    if event.key == p2.controls["swing"]:
                        p2.start_swing(now)
                else:
                    if event.key == pygame.K_r:
                        reset_round(p1,p2,arena_rect)
                        game_over = False
                        items.clear()

        if not game_over:
            keys = pygame.key.get_pressed()
            p1.handle_input(keys, now, arena_rect)
            p2.handle_input(keys, now, arena_rect)
            p1.update(now)
            p2.update(now)

            check_sword_hit(p1,p2,now)
            check_sword_hit(p2,p1,now)

            if p1.hp <=0 or p2.hp <=0:
                game_over = True

            # Item spawn
            if now - last_item_spawn > ITEM_SPAWN_INTERVAL and len(items)<3:
                ix = random.randint(arena_rect.left+40, arena_rect.right-40-ITEM_SIZE)
                iy = random.randint(arena_rect.top+40, arena_rect.bottom-40-ITEM_SIZE)
                items.append(Item((ix,iy)))
                last_item_spawn = now

            for item in items[:]:
                if p1.rect.colliderect(item.rect):
                    p1.hp = min(START_HP, p1.hp + HEAL_AMOUNT)
                    items.remove(item)
                elif p2.rect.colliderect(item.rect):
                    p2.hp = min(START_HP, p2.hp + HEAL_AMOUNT)
                    items.remove(item)

        draw_arena(screen, arena_rect)
        p1.draw(screen)
        p2.draw(screen)
        for item in items:
            item.draw(screen)
        draw_hud(screen, p1, p2, font, now)

        if game_over:
            winner = "P2" if p1.hp<=0 else "P1"
            msg = big_font.render(f"{winner} WINS! Press R to restart", True, WHITE)
            screen.blit(msg, (WIDTH//2 - msg.get_width()//2, HEIGHT//2 - msg.get_height()//2))

        pygame.display.flip()

    pygame.quit()
    sys.exit()


if __name__=="__main__":
    main()
