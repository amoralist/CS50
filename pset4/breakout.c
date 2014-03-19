//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows and columns of bricks
#define ROWS 5
#define COLS 10
// height and width of bricks and the spaces
    // between them in pixels
#define BRICK_HEIGHT 10
#define BRICK_WIDTH 30
#define SPACE_HEIGHT 6
#define SPACE_WIDTH 6

// free space at the top and left side of the 
    // window in pixels
#define OFFSET_HEIGHT 50
#define OFFSET_WIDTH 23

// Paddle's y position
#define PADDLE_Y 540

// radius of ball in pixels
#define RADIUS 10
// beginning position of ball in pixels
#define BALL_X 200
#define BALL_Y 300
// ball's velocity
#define VELOCITY 1

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);   

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // ball's x and y velocity
    double vel_x = VELOCITY;
    double vel_y = VELOCITY;
    
    // initialize zero'd scoreboard
    updateScoreboard(window, label, points);
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {        
        // check for collision with paddle or brick
        GObject collide_obj = detectCollision(window, ball);
        if (collide_obj != NULL && collide_obj != label) {    
            // paddle
            if (collide_obj == paddle)
                vel_y = -vel_y; 
            // brick
            else {
                vel_y = -vel_y;
                points += 1;
                updateScoreboard(window, label, points);
                removeGWindow(window, collide_obj);
            }
        }
        
        // check for window sides
        if (getX(ball) + RADIUS * 2 >= WIDTH || getX(ball) <= 0) {
            vel_x = -vel_x;
        }

        //check for window top and bottom
        if (getY(ball) <= 0)
            vel_y = -vel_y;
        else if (getY(ball) + RADIUS * 2 >= HEIGHT) {
            lives -= 1;
            removeGWindow(window, ball);
            ball = initBall(window);
            waitForClick();
        }
        
        // move the paddle
        GEvent mouse_event = getNextEvent(MOUSE_EVENT);
        if (mouse_event != NULL) {
            if (getEventType(mouse_event) == MOUSE_MOVED) {
                double x = getX(mouse_event);
                setLocation(paddle, x, PADDLE_Y);
            }
        }
        
        // move the ball
        move(ball, vel_x, vel_y);
        
        // check for premature window close
        GEvent window_event = getNextEvent(WINDOW_EVENT);
        if (window_event != NULL) {
            if (getEventType(window_event) == WINDOW_CLOSED) {
                closeGWindow(window);
                return 0;
            }
        }
        
        // pause for sanity
        pause(15);        
    }

    // wait for click before exiting normally after a win
    waitForClick();
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double draw_x = OFFSET_WIDTH;
    double draw_y = OFFSET_HEIGHT;
        
    for (int i = 0; i < ROWS; i++) {
        for (int n = 0; n < COLS; n++) {
           GRect brick = newGRect(draw_x, draw_y, BRICK_WIDTH, BRICK_HEIGHT);
           setColor(brick, "BLACK");
           setFilled(brick, true);
           add(window, brick);
           draw_x += BRICK_WIDTH + SPACE_WIDTH; 
        }
        draw_y += BRICK_HEIGHT + SPACE_HEIGHT;
        draw_x = OFFSET_WIDTH;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{   
    GOval ball = newGOval(BALL_X - RADIUS, BALL_Y, RADIUS * 2, RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - BRICK_WIDTH, PADDLE_Y, BRICK_WIDTH * 2, BRICK_HEIGHT / 2);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-36");
    setColor(scoreboard, "RED");
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
