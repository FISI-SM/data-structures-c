#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "gui_music.h"

Node *head = NULL;
Node *current = NULL;

typedef struct {
    SDL_Rect rect;
    const char *text;
} Button;

int point_in_rect(int x, int y, SDL_Rect r) {
    return (x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h);
}

SDL_Texture* render_text(SDL_Renderer *ren, TTF_Font *font, const char *text, SDL_Color color, int *w, int *h) {
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    if (w) *w = surf->w;
    if (h) *h = surf->h;
    SDL_FreeSurface(surf);
    return tex;
}

void draw_button(SDL_Renderer *ren, TTF_Font *font, Button btn) {
    SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
    SDL_RenderDrawRect(ren, &btn.rect);
    SDL_Color col = {230, 230, 230, 255};
    int tw=0, th=0;
    SDL_Texture *tt = render_text(ren, font, btn.text, col, &tw, &th);
    if (tt) {
        SDL_Rect dst = { btn.rect.x + (btn.rect.w - tw)/2, btn.rect.y + (btn.rect.h - th)/2, tw, th };
        SDL_RenderCopy(ren, tt, NULL, &dst);
        SDL_DestroyTexture(tt);
    }
}

int main() {
    append(&head, "Song 1 - Yesterday");
    append(&head, "Song 2 - Imagine");
    append(&head, "Song 3 - Let it Be");
    append(&head, "Song 4 - Hey Jude");
    current = head;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *win = SDL_CreateWindow("Music Browser (SDL2)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 520, 220, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont("font.ttf", 22);

    Button btnLeft  = { .rect = { 80,  140, 120, 40 }, .text = "Left"  };
    Button btnRight = { .rect = { 320, 140, 120, 40 }, .text = "Right" };

    int running = 1; SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x, my = e.button.y;
                if (point_in_rect(mx, my, btnLeft.rect)) {
                    Node *prev = find_prev(head, current);
                    if (prev) current = prev;
                } else if (point_in_rect(mx, my, btnRight.rect)) {
                    if (current && current->next) current = current->next;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 30, 30, 36, 255);
        SDL_RenderClear(ren);

        if (current) {
            SDL_Color white = {240, 240, 240, 255};
            int tw, th;
            SDL_Texture *songTex = render_text(ren, font, current->song, white, &tw, &th);
            SDL_Rect dst = { (520 - tw)/2, 50, tw, th };
            SDL_RenderCopy(ren, songTex, NULL, &dst);
            SDL_DestroyTexture(songTex);
        }

        draw_button(ren, font, btnLeft);
        draw_button(ren, font, btnRight);

        SDL_RenderPresent(ren);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
