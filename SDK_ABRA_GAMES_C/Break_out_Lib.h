
//{-----------------------------------------------------------------------------
//! @brief         Arcade game "BREAK OUT"
//!
//! @author        Abramova Irina,
//!             Krasnodar, gimnasium 36
//!
//!
//! @date            August, 2021
//!
//! @mainpage
//!                  ������ �������:
//!
//!                - @ref Blocks::Draw_Blocks();
//!                - @ref Ball::Draw_Ball();
//!                - @ref Ball::Physics_Ball();
//!                - @ref Paddle::Draw_Paddle();
//!                - @ref Paddle::Physics_Paddle_Mouse();
//!                - @ref ButtonType::ButtonCheckClick();
//!                - @ref ButtonType::Menu();
//!                - @ref Fill_array();
//!                - @ref Print_array();
//!                - @ref Control_CollisionsBP();
//!                - @ref Control_CollisionsBB();
//!                - @ref Cycling();
//!                - @ref OutputScore();
//!
//! @section screenshots
//!
//! @image html Break_out_screen.png
//}-------------------------------------------------------------------------------------------------

#define SIZE_ROWS 6
#define SIZE_COLS 9
#define ORIGIN_X 10
#define ORIGIN_Y 70
#define LEFT_EDGE_WINDOW 0
#define RIGHT_EDGE_WINDOW 780
#define TOP_WINDOW 0
#define BOTTON_WINDOW 700
#define GAME_STATE_INIT 0
#define GAME_START_LEVEL 1
#define GAME_STATE_RUN   2
#define GAME_STATE_SHUTDOWN 3
#define GAME_STATE_EXIT 4
#define AMOUNT_OF_LEVELS 3


struct Blocks
    {
    int x, y;
    int width, height;
    int GapX, GapY;
    int block_hit;

    void Draw_Blocks (int arr[SIZE_ROWS][SIZE_COLS]);
    };


struct Level
    {
    int max_score;
    int score;
    int number_level;
    int game_state;
    char legend_score[20];
    char legend_level[20];
    char legend_max_score[20];
    };


struct Ball
    {
    double x, y;
    double vx, vy;
    int radius;
    int missed_balls;

    void Draw_Ball();
    void Physics_Ball (double dt, Level* level);
    };


struct Paddle
    {
    double x, y;
    int width;
    int height;

    void Draw_Paddle();
    void Physics_Paddle_Mouse();
    };


struct ButtonType
    {
    int x, y;
    int dis_x, dis_y;
    int ButtonCheckClick (int mouse_x, int mouse_y);
    void Menu (Level* level, Ball* ball);
    };

Blocks Set    = {10, 50, 80, 20, 85, 25, 0};
Ball ball     = {400, 400, 15, 15, 10, 0};
Paddle paddle = {0, 600, 180, 20};
Level level   = {0, 0, 1, 0, "SCORE", "LEVEL", "BEST RESULT"};

ButtonType Start      = {300, 330, 160, 70};
ButtonType Play_icon  = {590,  25,  30, 20};
ButtonType Pause_icon = {640,  25,  30, 20};
ButtonType Exit_icon  = {690,  25,  30, 20};
ButtonType Restart    = {270, 620, 210, 40};
ButtonType Exit       = {305, 455, 155, 65};


double dt  = 1.0;
int arr[SIZE_ROWS][SIZE_COLS]{};


void Fill_array  (int arr[SIZE_ROWS][SIZE_COLS]);

void Print_array (int arr[SIZE_ROWS][SIZE_COLS]);

void Control_CollisionsBP (Ball* ball, Paddle* paddle);

void Control_CollisionsBB (int arr[SIZE_ROWS][SIZE_COLS], Ball* ball,
                           Blocks* Set, Level* level, Paddle* paddle);

void Cycling (Level level);

void OutputScore (Level* level, int tablo_x, int tablo_y, COLORREF color_score);


//{------------------------------------------------------------------------------------------------
//!         ��� ������� ��������� ������ �������
//!
//!         � �������� ��������� � ������� ���������� ��������� ������  arr[][]
//!
//!  @see   Blocks::Draw_blocks (int arr[SIZE_ROWS][SIZE_COLS])
//!
//!  @note  ������ ����������� ��� ��������� ������ ������, �������� ��������� ���������� ���� �����
//}-------------------------------------------------------------------------------------------------

void Fill_array (int arr[SIZE_ROWS][SIZE_COLS])
    {
    for (int i = 0; i < SIZE_ROWS; i ++)
        {
        for (int j = 0; j < SIZE_COLS; j ++)
            {
            arr[i][j] = i*16 + j*3 + 16;
            }
        }
    }

//{------------------------------------------------------------------------------------------------
//!         ��� ������� ������� �������� ��������� ���������� �������.
//!
//!         � �������� ��������� � ������� ���������� ��������� ������  arr[][]
//!
//!  @see   Control_CollisionsBB();
//!
//!  @note  ������� ������������ ��� ���������������, ��� �������� ������
//!  @note  ������� �������� ������������ ���� � ������:  Control_CollisionsBB();
//}-------------------------------------------------------------------------------------------------

void Print_array (int arr[SIZE_ROWS][SIZE_COLS])
    {
    for (int i = 0; i < SIZE_ROWS; i ++)
        {
        for (int j = 0; j < SIZE_COLS; j ++)
            {
            printf ("%5d ", arr[i][j]);
            }
        printf("\n");
        }
    }

//{------------------------------------------------------------------------------------------------
//!    ��� ������� ����� ������ Blocks, ������ ����� ������������ ������.
//!
//!    ����� ���������� ����� ���������, � �������� ��������� ���������� ��������� ������  arr[][]
//!
//! @param  x                 x - ���������� �������� ������ ���� �����
//! @param  y                 y - ���������� �������� ������ ���� �����
//! @param  width             ������ �����
//! @param  height            ������ �����
//! @param  GapX              ���������� �� ������ �������� ���� ���������� � ���� �����
//! @param  GapY              ���������� �� ������ �������� ���� ���������� � ������� �����
//!
//! @par    ������ �������������:
//!
//! @code
//!         Set.Draw_blocks (arr);
//! @endcode
//}-------------------------------------------------------------------------------------------------

void Blocks::Draw_Blocks (int arr[SIZE_ROWS][SIZE_COLS])
    {
    for (int i = 0; i < SIZE_ROWS; i ++)
        {
        x = ORIGIN_X;
        for (int j = 0; j < SIZE_COLS; j ++)
            {
            if (arr[i][j]!= 0)
                {
                txSetColor     (RGB (100 + arr[i][j] , 200 - arr[i][j] , 5 + arr[i][j]), 2);
                txSetFillColor (RGB (100 + arr[i][j] , 200 - arr[i][j] , 5 + arr[i][j]));
                txRectangle(x, y, x + width, y + height);
                }
                x += GapX;
            }
            y += GapY;
        }
    y = ORIGIN_Y;
    }

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ����� ������ Ball, ������  ���.
//!
//! @param  x                           x - ���������� ������ ����
//! @param  y                           y - ���������� ������ ����
//! @param  radius                      ������ ����
//!
//! @par    ������ �������������:
//!
//! @code
//!         ball.Draw_Ball();
//! @endcode
//}----------------------------------------------------------------------------------------------

void Ball::Draw_Ball()
    {
    txSetColor     (RGB ( 204, 102, 50), 2);
    txSetFillColor (RGB ( 204, 102, 50));
    txCircle (x, y, radius);
    }

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ����� ����� ������ Ball, ��������� �������� ����.
//!
//! @param  double dt                   ���������� ������� (dt = 1.0)
//! @param  x                           x - ���������� ������ ����
//! @param  y                           y - ���������� ������ ����
//! @param  vx                          �������� ���� �� x
//! @param  vy                          �������� ���� �� y
//! @param  radius                      ������ ����
//! @param  missed_balls                ����������� ����
//!
//! @param  (*level).score              ������� ���� ����
//! @param  (*level).game_state         ��������� ����
//!
//! @par    ������ �������������:
//!
//! @code
//!         ball.Physics_Ball (dt, &level);
//! @endcode
//}----------------------------------------------------------------------------------------------

void Ball::Physics_Ball (double dt, Level* level)
    {
    x = x + vx * dt;
    y = y + vy * dt;

    if (x >= RIGHT_EDGE_WINDOW - radius)
        {
        txPlaySound ("Resourses\\hit.wav", SND_ASYNC);
        vx = - vx;
        x  = RIGHT_EDGE_WINDOW - radius;
        }

    if (y >= BOTTON_WINDOW - radius)
        {
        txPlaySound ("Resourses\\poolpot.wav", SND_ASYNC);
        missed_balls += 1;
        (*level).score -= 50;
        y  = BOTTON_WINDOW/2 - radius;
        }

    if (x <= LEFT_EDGE_WINDOW + radius)
        {
        txPlaySound ("Resourses\\hit.wav", SND_ASYNC);
        vx = - vx;
        x  = LEFT_EDGE_WINDOW + radius;
        }

    if (y <= TOP_WINDOW + radius)
        {
        txPlaySound ("Resourses\\hit.wav", SND_ASYNC);
        vy = - vy;
        y  = TOP_WINDOW + radius;
        }

    if (missed_balls == 10)
        {
        txPlaySound ("Resourses\\ICE.wav", SND_ASYNC);
        ((*level).game_state) = GAME_STATE_EXIT;
        }
    if (vx >= 25) vx -= 5;
    }

//{----------------------------------------------------------------------------------------------
//!         ��� �������  ����� ������ Paddle, ������ �������.
//!
//! @param  txMouseX()          ����������  x, ���������� �������� ������ ����
//! @param  y                   ����������  y, ���������� �������� ������ ����
//! @param  Paddle_width        ������ �������
//! @param  Paddle_height       ������ �������
//!
//! @par    ������ �������������:
//!
//! @code
//!         paddle.Draw_Paddle();
//! @endcode
//}----------------------------------------------------------------------------------------------

void Paddle::Draw_Paddle()
    {
    txSetColor     (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txRectangle (txMouseX(), y, txMouseX() + width, y + height);
    }

//{----------------------------------------------------------------------------------------------
//!         ��� �������  ����� ������ Paddle, ��������� �������� �������.
//!
//! @param  x          ������� ����������  x ������� (���������� �������� ������ ����)
//!
//!
//! @par    ������ �������������:
//!
//! @code
//!         paddle.Draw_Paddle();
//! @endcode
//!
//! @note   ������� ��������� ��  ������, ��� ������ �������   txMouseX()
//}----------------------------------------------------------------------------------------------

void Paddle:: Physics_Paddle_Mouse()
    {
    x = txMouseX();
    }

int  Check_distanse (Paddle paddle1, Ball ball1)
    {
    if ((ball1.x + ball1.radius >= paddle1.x)
        && (ball1.x + ball1.radius <= paddle1.x + paddle1.width)
        && (ball1.y + ball1.radius >= paddle1.y)
        && (ball1.y + ball1.radius <= paddle1.y + paddle1.height))
    return 1;
    else
    return 0;
    }



//{----------------------------------------------------------------------------------------------
//!         ��� ������� ��������� ������������ ����� ����� � ��������.
//!
//!         ��������� � �������� ���������� ��������� Ball � Paddle
//!
//! @param  (*ball).x                x - ���������� ������ ����
//! @param  (*ball).y                y - ���������� ������ ����
//! @param  (*ball).radius           ������ ����
//! @param  (*ball).vx               �������� ���� �� x
//! @param  (*ball).vy               �������� ���� �� y
//!
//! @param  (*paddle).x              x - ���������� ������ �������� ���� �������
//! @param  (*paddle).y              y - ���������� ������ �������� ���� �������
//! @param  (*paddle).Paddle_width   ������ �������
//! @param  (*paddle).Paddle_height  ������ �������
//!
//! @par    ������ �������������:
//!
//! @code
//!         Control_CollisionsBP (&ball, &paddle);
//! @endcode
//}----------------------------------------------------------------------------------------------

void Control_CollisionsBP (Ball* ball, Paddle* paddle)
    {
    if (((*ball).x + (*ball).radius >= (*paddle).x)
        && ((*ball).x + (*ball).radius <= ((*paddle).x + (*paddle).width))
        && ((*ball).y + (*ball).radius >= (*paddle).y)
        && ((*ball).y + (*ball).radius <= ((*paddle).y + (*paddle).height)))
        {
        txPlaySound ("Resourses\\hit.wav", SND_ASYNC);
        (*ball).vy =- (*ball).vy;
        (*ball).vy = - 1.0f * abs((*ball).vy);
        (*ball).y  += (*ball).vy;

        if ((*paddle).x < RIGHT_EDGE_WINDOW/2) (*ball).vx -= (rand()%10);

        if ((*paddle).x > RIGHT_EDGE_WINDOW/2) (*ball).vx += (rand()%10);
        else
         (*ball).vx += (-1 + rand()%10);
        }
    }

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ��������� ������������ ����� ����� � �������.
//!
//!         ��������� � �������� ���������� ������ arr[][], ��������� Ball, Paddle, Level
//!
//! @param  (*ball).x                x - ���������� ������ ����
//! @param  (*ball).y                y - ���������� ������ ����
//! @param  (*ball).radius           ������ ����
//! @param  (*ball).vx               �������� ���� �� x
//! @param  (*ball).vy               �������� ���� �� y
//!
//! @param  (*Set).block_hit         ���������� ������� ������
//! @param  (*Set).x                 x - ���������� �������� ������ ���� �����
//! @param  (*Set).y                 y - ���������� �������� ������ ���� �����
//! @param  (*Set).width             ������ �����
//! @param  (*Set).height            ������ �����
//! @param  (*Set).GapX              ���������� �� ������ �������� ���� ���������� � ���� �����
//! @param  (*Set).GapY              ���������� �� ������ �������� ���� ���������� � ������� �����
//!
//! @param  (*paddle).Paddle_width   ������ �������
//! @param  (*paddle).Paddle_height  ������ �������
//!
//! @param  (*level).game_state      ��������� ����
//! @param  (*level).max_score       ������������ ���� �� ����
//! @param  (*level).score           ������� ���� �� �������
//! @param  (*level).number_level    ����� ������
//!
//!
//! @par    ������ �������������:
//!
//! @code
//!         Control_CollisionsBB (arr, &ball, &Set, &level, &paddle);
//! @endcode
//}----------------------------------------------------------------------------------------------

void Control_CollisionsBB (int arr[SIZE_ROWS][SIZE_COLS],  Ball* ball, Blocks* Set, Level* level, Paddle* paddle)
    {
    if ((*Set).block_hit == SIZE_ROWS*SIZE_COLS)
        {
        (*Set).block_hit = 0;
        (*level).game_state = GAME_START_LEVEL;
        if ((*level).score > (*level).max_score) (*level).max_score = (*level).score;
        (*level).score = 0;
        (*level).number_level ++;
        (*ball).x = 400;
        (*ball).y = 400;

        (*paddle).width -= 45;

        if ((*level).number_level == AMOUNT_OF_LEVELS + 1 )
            {
            (*level).number_level = 1;
            (*paddle).width = 180;
            (*level).game_state = GAME_STATE_SHUTDOWN;
            }
        }

     for (int i = 0; i < SIZE_ROWS; i ++)
        {
        (*Set).x = ORIGIN_X;
        for (int j = 0; j < SIZE_COLS; j ++)
            {
            if (arr[i][j]!=0)
                {
                if (((*ball).x + (*ball).radius > (*Set).x)
                    && ((*ball).x + (*ball).radius < ((*Set).x + (*Set).width))
                    && ((*ball).y + (*ball).radius > (*Set).y)
                    && ((*ball).y + (*ball).radius < ((*Set).y + (*Set).height)))
                    {
                    txPlaySound ("Resourses\\BIT.wav", SND_ASYNC);
                    (*Set).block_hit += 1;
                    (*level).score += 15;
                    arr[i][j] = 0;
                    (*ball).vy = -(*ball).vy;
                    (*ball).vx += (rand()%3);
                    }
                }
            (*Set).x += (*Set).GapX;
            }
        (*Set).y += (*Set).GapY;
        }
    (*Set).y = ORIGIN_Y;
   }

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ������� �� ����� ���������� ����
//!
//!         ��������� � �������� ���������� �������� Level
//!
//! @param  (*level).max_score         ������������ ���� �� ����
//! @param  (*level).score             ������� ���� �� �������
//! @param  (*level).number_level      ����� ������
//! @param  (*level).legend_score      �������
//! @param  (*level).legend_level      �������
//! @param  (*level).legend_max_score  �������
//!
//! @param   tablo_x                   x - ���������� ������ �������
//! @param   tablo_y                   y - ���������� ������ �������
//! @param   COLORREF color_score      ���� �������
//!
//! @par    ������ �������������:
//!
//! @code
//!         OutputScore (&level, 90, 650, TX_YELLOW);
//! @endcode
//}----------------------------------------------------------------------------------------------

void OutputScore (Level* level, int tablo_x, int tablo_y, COLORREF color_score)
    {
    txSelectFont ("Times", 26, 10);
    char str [100] = "";
    sprintf (str, "%s: %-16d %s: %-16d %s: %d",
            (*level).legend_score, (*level).score,
            (*level).legend_level, (*level).number_level,
            (*level).legend_max_score, (*level).max_score);
    txSetColor (color_score);
    txSetFillColor (color_score);
    txTextOut (tablo_x, tablo_y, str);
    }

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ����� ������ ButtonType, ���������� "1" ��� ������� �� ������
//!
//!         ��������� � �������� ���������� ������� ���������� �����
//!
//! @note   ��������������� �������, �����������  ������� ����� � ������������ ������� �������
//!
//! @param  x           x - ���������� �������� ������ ���� ������������ ������
//! @param  y           y - ���������� �������� ������ ���� ������������ ������
//!
//! @param  mouse_x     x - ������� ���������� �����
//! @param  mouse_y     y - ������� ���������� �����
//!
//! @param  dis_x       ����������� �������� �� x,  ����� ������� ������������ ������ � ������� ����������� x �����
//! @param  dis_y       ����������� �������� �� y,  ����� ������� ������������ ������ � ������� ����������� y �����
//!
//!
//! @par    ������ �������������:
//!
//! @code
//!         if (Pause_icon.ButtonCheckClick (txMouseX(), txMouseY()) == true)
//!             {
//!             (*ball).vx = 0;
//!             (*ball).vy = 0;
//!             }
//! @endcode
//}----------------------------------------------------------------------------------------------

int ButtonType::ButtonCheckClick (int mouse_x, int mouse_y)
    {
    if (fabs (x - mouse_x) <= dis_x)
        if (fabs (y - mouse_y) <= dis_y)
            if (GetAsyncKeyState (VK_LBUTTON))
                {
                return 1;
                };
    return 0;
    };

//{----------------------------------------------------------------------------------------------
//!         ��� ������� ����� ������ ButtonType, ��������� ������ ������ � ����
//!
//!         ��������� � �������� ���������� ��������� Level � Ball
//!
//! @param  (*level).game_state      ��������� ����
//!
//! @param  (*ball).vx               �������� ���� �� x
//! @param  (*ball).vy               �������� ���� �� y
//!
//! @par    ������ �������������:
//!
//! @code
//!         Pause_icon.Menu (&level, &ball);
//!         Play_icon.Menu  (&level, &ball);
//!         Exit_icon.Menu  (&level, &ball);
//! @endcode
//}----------------------------------------------------------------------------------------------

void ButtonType::Menu (Level* level, Ball* ball)
    {
    if (Start.ButtonCheckClick (txMouseX(), txMouseY()) == true) (*level).game_state = GAME_START_LEVEL;
    if (Pause_icon.ButtonCheckClick (txMouseX(), txMouseY()) == true)
        {
        (*ball).vx = 0;
        (*ball).vy = 0;
        }
    if (Play_icon.ButtonCheckClick (txMouseX(), txMouseY()) == true)
        {
        (*ball).vx = 15;
        (*ball).vy = 15;
        }
    if (Exit_icon.ButtonCheckClick (txMouseX(), txMouseY()) == true) (*level).game_state = GAME_STATE_EXIT;
    if (Exit.ButtonCheckClick (txMouseX(), txMouseY()) == true) (*level).game_state = GAME_STATE_EXIT;
    if (Restart.ButtonCheckClick (txMouseX(), txMouseY()) == true) (*level).game_state = GAME_STATE_INIT;
    }
