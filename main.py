import pygame
import math
from dice import Die, Die_face, STANDARD_DIE

width = 960
height = 540
scale = width/(960/1.3) #keep this for resizing window
pygame.init()
pygame.font.init()
screen = pygame.display.set_mode((width,height))
pygame.display.set_caption("Dice")
die_number_font = pygame.font.SysFont("Arial", int(30*scale))

WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
ORANGE = (255,140,0)
YELLOW = (255,255,0)
GREEN = (0,255,0)
BLUE = (255,0,255)

def draw_die(screen,die:Die,pos:tuple):
    pygame.draw.rect(screen,WHITE,(pos[0]*scale,pos[1]*scale,50*scale,50*scale),border_radius=12)
    number = die_number_font.render(str(die.last_roll), False, (0, 0, 0))
    number_rect = number.get_rect(center=(pos[0]*scale+25*scale,pos[1]*scale+25*scale))
    screen.blit(number, number_rect)

dice:list[Die] = [STANDARD_DIE]*2

state = "rolling"

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            continue
    screen.fill((10,10,10))
    if state == "rolling":
        # input
        if pygame.mouse.get_just_pressed()[0]:
            for die in dice:
                die.roll()
        # drawing
        posMod = math.ceil(math.log(len(dice), 3))
        rowCount = (posMod) * 2 + 1

        for i, die in enumerate(dice):
            draw_die(screen, die, (
                width / (2 * scale) - 50 * scale - (((posMod - i % rowCount) * 55 + rowCount / 2) * 55 * scale),
                height / (2 * scale) - 50 * scale - (((posMod - i / rowCount) * 55 + rowCount / 2) * 55 * scale)
            ))
    pygame.display.update()
pygame.quit()