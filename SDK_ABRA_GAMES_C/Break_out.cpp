#include <stdlib.h>
#include <random>
#include "TXLib.h"
#include "time.h"
#include "Break_out_Lib.h"



int main()
    {
    txCreateWindow (RIGHT_EDGE_WINDOW, BOTTON_WINDOW);

    Cycling (level);

    return 0;
    }

void Cycling (Level level)
    {
    HDC  Playing_field_View_start  = txLoadImage ("Resourses\\fon_entry.bmp");
    HDC  Playing_field_View_run    = txLoadImage ("Resourses\\fon_run.bmp");
    HDC  Playing_field_View_passed = txLoadImage ("Resourses\\fon_finish_victory.bmp");
    HDC  Playing_field_View_over   = txLoadImage ("Resourses\\fon_finish.bmp");
    bool quit = false;

    while (!quit)
        {
        switch (level.game_state)
            {
            case GAME_STATE_INIT:
                {
                txBitBlt  (txDC(), 0, 0, RIGHT_EDGE_WINDOW, BOTTON_WINDOW, Playing_field_View_start, 0, 0);
                Start.Menu(&level, &ball);
                Exit.Menu (&level, &ball);
                }break;

            case GAME_START_LEVEL:
                {
                Fill_array  (arr);
                level.game_state = GAME_STATE_RUN;
                }break;

            case GAME_STATE_RUN:
                {
                txBitBlt  (txDC(), 0, 0, RIGHT_EDGE_WINDOW, BOTTON_WINDOW, Playing_field_View_run, 0, 0);
                paddle.Physics_Paddle_Mouse();
                Set.Draw_Blocks (arr);
                ball.Physics_Ball (dt, &level);

                Control_CollisionsBP (&ball, &paddle);
                Control_CollisionsBB (arr, &ball, &Set, &level, &paddle);
                //Print_array (arr);
                paddle.Draw_Paddle();
                ball.Draw_Ball();

                OutputScore (&level, 90, 650, TX_YELLOW);
                Pause_icon.Menu (&level, &ball);
                Play_icon.Menu  (&level, &ball);
                Exit_icon.Menu  (&level, &ball);
                }break;

            case GAME_STATE_SHUTDOWN:
                {
                txBitBlt  (txDC(), 0, 0, RIGHT_EDGE_WINDOW, BOTTON_WINDOW, Playing_field_View_passed, 0, 0);
                Restart.Menu (&level, &ball);
                if (txGetAsyncKeyState (VK_ESCAPE)) level.game_state = GAME_STATE_EXIT;
                }break;

            case GAME_STATE_EXIT:
                {
                quit = true;
                txBitBlt  (txDC(), 0, 0, RIGHT_EDGE_WINDOW, BOTTON_WINDOW, Playing_field_View_over, 0, 0);
                }break;
            default:
                break;
            }
        txSleep (30);
        }
    txDeleteDC (Playing_field_View_start);
    txDeleteDC (Playing_field_View_run);
    txDeleteDC (Playing_field_View_passed);
    txDeleteDC (Playing_field_View_over);
    }
