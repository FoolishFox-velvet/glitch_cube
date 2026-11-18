#include <raylib.h>
#include <utility>

constexpr int window_width{1920};
constexpr int window_height{1080};
constexpr int num_rows{30};
constexpr int num_columns{30};
constexpr int num_depth{30};
float cell_size{1};
int glitch_bias{1};

int space[num_rows][num_columns][num_depth];


int j = 0;
int i = 0;
int l = 0;

void Draw(){
    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){
            for(int d{0}; d < num_depth; d++){

                if(space[r][c][d]==1){
                Color randcolor{static_cast<unsigned char>(GetRandomValue(0, 255)),
                    static_cast<unsigned char>(GetRandomValue(0, 255)),static_cast<unsigned char>(GetRandomValue(0, 255)),255};
                DrawCube({float(r)+j,float(c)+l,float(d)+i}, cell_size, cell_size, cell_size, randcolor);
                i++;
                if(i == glitch_bias)i=0;
                }
            l++;
            if(l == glitch_bias)l=0;
            }
        }
        j++;
        if(j == glitch_bias)j=0;
    }
}

int CountNeighbors(int r, int c, int d){
    int count{0};
    int range{1};
    int neighborR;
    int neighborC;
    int neighborD;

    for(int dr{-range}; dr <= range; dr++){
        for(int dc{-range}; dc<=range; dc++){
            for(int dd{-range};dd<=range;dd++){
                if(dr==0 && dc==0 && dd == 0)continue;
                neighborR = (r + dr + num_rows) % num_rows;
                neighborC = (c + dc + num_columns) % num_columns;
                neighborD = (d + dd + num_depth) % num_depth;
                count += space[neighborR][neighborC][neighborD];
            }
        }
    }
    return count;
}  

void Update(){
    int tempspace[num_rows][num_columns][num_depth];

    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){
            for(int d{0}; d < num_depth; d++){
                int neighbor_count = CountNeighbors(r, c, d);
                if (neighbor_count == 4) {
                    tempspace[r][c][d] = 1;
                }
                else if (space[r][c][d] == 1 && (neighbor_count == 3 || neighbor_count == 4)) {
                    tempspace[r][c][d] = 1; 
                }
                else {
                    tempspace[r][c][d] = 0;
                }
            }
        }
    }

    std::swap(space, tempspace);
   
}


int main(){
    InitWindow(window_width, window_height, "3d");
    SetTargetFPS(60);
    Camera3D camera{{8,12,-40},{8,12,-5},{0,1,0},45,CAMERA_PERSPECTIVE};

    for(int r{0}; r < num_rows; r++){
        for(int c{0}; c < num_columns; c++){
            for(int d{0}; d < num_depth; d++){
                space[r][c][d] = (GetRandomValue(0, 99) < 12) ? 1 : 0;
            }
        }
    }

    DisableCursor();

    float updateTimer = 0.0f;
    const float updateInterval = .2f;

    while(!WindowShouldClose()){
        UpdateCamera(&camera, CAMERA_FREE);

        updateTimer += GetFrameTime();
        if(updateTimer >= updateInterval) {
            Update();
            updateTimer = 0.0f;
        }

        if(IsKeyDown(KEY_G) && IsKeyDown(KEY_RIGHT) && glitch_bias < 100)glitch_bias++;
        if(IsKeyDown(KEY_G) && IsKeyDown(KEY_LEFT) && glitch_bias > 1){glitch_bias--;j=0;l=0;i=0;}
        if(IsKeyDown(KEY_C) && IsKeyDown(KEY_RIGHT) && cell_size < 10)cell_size+=0.1;
        if(IsKeyDown(KEY_C) && IsKeyDown(KEY_LEFT) && cell_size > 0.3)cell_size-=0.1;

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);


        DrawGrid(100,1.0f);
        Draw();

        
        
        EndMode3D();
        DrawText(TextFormat("Glitch Bias: %i", glitch_bias), 25, 25, 25, WHITE);
        DrawText(TextFormat("Cell Size: %.1f", cell_size), 25, 65, 25, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
