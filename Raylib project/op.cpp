// ---------------- BULLETS / LASERS ----------------
    const int MAX_BULLETS = 10;
    int BulletX[MAX_BULLETS];
    int BulletY[MAX_BULLETS];
    int BulletActive[MAX_BULLETS];
    int bi = 0;
    while (bi < MAX_BULLETS)
    {
        BulletActive[bi] = 0;
        BulletX[bi] = 0;
        BulletY[bi] = 0;
        bi++;
    }
    int BulletSpeed = 7;

    // ---------------- SCORE & LEVEL ----------------
    int Score = 0;
    int Level = 1;

    // ---------------- FIRE COOLDOWN ----------------
    int FireCooldown = 0;
    const int FireCooldownMax = 15;

    // ---------------- START SCREEN ----------------
    bool gameStarted = false;
    while (!gameStarted && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);

        DrawText("SPACE SHOOTER", WindowWidth / 2 - 180, WindowHeight / 2 - 80, 50, SKYBLUE);
        DrawText("Press ENTER to Start", WindowWidth / 2 - 150, WindowHeight / 2 + 20, 30, WHITE);
        DrawText("Use LEFT/RIGHT arrows to move", WindowWidth / 2 - 200, WindowHeight / 2 + 70, 20, LIGHTGRAY);
        DrawText("Press SPACE to shoot", WindowWidth / 2 - 150, WindowHeight / 2 + 100, 20, LIGHTGRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            gameStarted = true;
    }

    // ---------------- MAIN GAME LOOP ----------------
    while (!WindowShouldClose())
    {
        // -------- PLAYER MOVEMENT --------
        if (IsKeyDown(KEY_LEFT)) ShipW -= ShipSpeed;
        if (IsKeyDown(KEY_RIGHT)) ShipW += ShipSpeed;
        if (ShipW < 20) ShipW = 20;
        if (ShipW > WindowWidth - 20) ShipW = WindowWidth - 20;

        // -------- SHOOT BULLETS --------
        if (FireCooldown > 0) FireCooldown--;
        if (IsKeyDown(KEY_SPACE) && FireCooldown == 0)
        {
            int bi2 = 0;
            while (bi2 < MAX_BULLETS)
            {
                if (!BulletActive[bi2])
                {
                    BulletActive[bi2] = 1;
                    BulletX[bi2] = ShipW;
                    BulletY[bi2] = ShipH - 18;
                    FireCooldown = FireCooldownMax;
                    break;
                }
                bi2++;
            }
        }

        // -------- BULLET UPDATE --------
        int bu = 0;
        while (bu < MAX_BULLETS)
        {
            if (BulletActive[bu])
            {
                BulletY[bu] -= BulletSpeed;
                if (BulletY[bu] < -10) BulletActive[bu] = 0;
            }
            bu++;
        }

        // -------- ENEMY MOVEMENT & COLLISION --------
        int ej = 0;
        while (ej < MAX_ENEMIES)
        {
            EnemyY[ej] += EnemySpeed[ej];

            // Enemy reaches bottom -> player loses life
            if (EnemyY[ej] > WindowHeight)
            {
                PlayerLives--;
                EnemyY[ej] = GetRandomValue(-400, -50);
                EnemyX[ej] = GetRandomValue(50, WindowWidth - 50);
                EnemySpeed[ej] = GetRandomValue(2 + Level, 4 + Level); // speed increases with level
            }

            // Bullet collision
            int bu2 = 0;
            while (bu2 < MAX_BULLETS)
            {
                if (BulletActive[bu2])
                {
                    int dx = BulletX[bu2] - EnemyX[ej];
                    int dy = BulletY[bu2] - EnemyY[ej];
                    if ((dx * dx + dy * dy) < 20 * 20) // simple radius collision
                    {
                        Score += 10;
                        BulletActive[bu2] = 0;
                        EnemyY[ej] = GetRandomValue(-400, -50);
                        EnemyX[ej] = GetRandomValue(50, WindowWidth - 50);
                        EnemySpeed[ej] = GetRandomValue(2 + Level, 4 + Level);
                    }
                }
                bu2++;
            }

            ej++;
        }

        // -------- LEVEL UP --------
        if (Score >= Level * 50)
        {
            Level++;
            // optional: increase enemy speed for all enemies
            int ei2 = 0;
            while (ei2 < MAX_ENEMIES)
            {
                EnemySpeed[ei2] += 1;
                ei2++;
            }
        }

        // -------- DRAWING --------
        BeginDrawing();
        ClearBackground(grey);

        // Draw player ship
        DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);
        DrawCircle(ShipW, ShipH - 5, 7, BLUE);
        DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);
        DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);

        // Draw bullets
        int bd = 0;
        while (bd < MAX_BULLETS)
        {
            if (BulletActive[bd])
                DrawCircle(BulletX[bd], BulletY[bd], 4, RAYWHITE);
            bd++;
        }

        // Draw enemies
        int ed = 0;
        while (ed < MAX_ENEMIES)
        {
            DrawRectangle(EnemyX[ed] - 18, EnemyY[ed] - 12, 36, 24, RED);
            DrawCircle(EnemyX[ed], EnemyY[ed] - 3, 8, YELLOW);
            DrawCircle(EnemyX[ed] - 15, EnemyY[ed] - 15, 6, MAROON);
            DrawCircle(EnemyX[ed] + 15, EnemyY[ed] - 15, 6, MAROON);
            DrawCircle(EnemyX[ed] - 25, EnemyY[ed] + 5, 7, MAROON);
            DrawCircle(EnemyX[ed] + 25, EnemyY[ed] + 5, 7, MAROON);
            DrawCircle(EnemyX[ed] - 8, EnemyY[ed] + 16, 6, ORANGE);
            DrawCircle(EnemyX[ed] + 8, EnemyY[ed] + 16, 6, ORANGE);
            ed++;
        }

        // Draw HUD: score and lives
        DrawText(TextFormat("Score: %i", Score), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Lives: %i", PlayerLives), WindowWidth - 120, 10, 20, RAYWHITE);
        DrawText(TextFormat("Level: %i", Level), WindowWidth / 2 - 50, 10, 20, YELLOW);

        // GAME OVER
        if (PlayerLives <= 0)
        {
            DrawText("GAME OVER", WindowWidth / 2 - 120, WindowHeight / 2 - 20, 40, RED);
            DrawText("Press ENTER to Restart", WindowWidth / 2 - 150, WindowHeight / 2 + 40, 20, WHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                // reset everything
                PlayerLives = MaxLives;
                Score = 0;
                Level = 1;
                ShipW = WindowWidth / 2;

                int ei3 = 0;
                while (ei3 < MAX_ENEMIES)
                {
                    EnemyX[ei3] = GetRandomValue(50, WindowWidth - 50);
                    EnemyY[ei3] = GetRandomValue(-500, -50);
                    EnemySpeed[ei3] = GetRandomValue(2, 4);
                    ei3++;
                }

                int bu3 = 0;
                while (bu3 < MAX_BULLETS)
                {
                    BulletActive[bu3] = 0;
                    bu3++;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
