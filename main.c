
#include "stdio.h"
#include "raylib.h"
#include <string.h>

#include "lector_nivel.h"

typedef struct Personaje
{
    Vector2 posicion;
    Texture textura;
    int casillaX;
    int casillaY;
} Personaje;

typedef struct Caja
{
    Vector2 posicion;
    Texture textura;
    int casillaX;
    int casillaY;
} Caja;

typedef struct Sensor
{
    Vector2 posicion;
    Texture textura;
    int casillaX;
    int casillaY;
} Sensor;

int matrizAArreglo(int columnas, int i, int j) {
    return j*columnas+i;
}

bool moverCaja(int nX, int nY, struct Caja *caja, int *nivel, int dims[2]) {
    bool movExitoso = false;
    int indiceEspacio = matrizAArreglo(dims[0], nX, nY);
    if (nivel[indiceEspacio] != -1) {
        int viejoIndiceCaja = matrizAArreglo(dims[0], caja->casillaX, caja->casillaY);
        nivel[viejoIndiceCaja] = 1;
        caja->casillaX = nX;
        caja->casillaY = nY;
        int nuevoIndiceCaja = matrizAArreglo(dims[0], caja->casillaX, caja->casillaY);
        nivel[nuevoIndiceCaja] = 2;
        movExitoso = true;  
    } 

    return movExitoso;
}

int main() 
{
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int tamCelda = 64;
    
    Personaje personaje = { 0 };

    InitWindow(screenWidth, screenHeight, "raylib");

    personaje.textura = LoadTexture("sprites/player_01.png"); 

    Texture piso = LoadTexture("sprites/ground_01.png");
    Texture pared = LoadTexture("sprites/block_01.png");
    Texture caja = LoadTexture("sprites/crate_01.png");
    Texture sensor = LoadTexture("sprites/environment_03.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    printf("Sumando dos numeros %d", Sum(2, 3));
    int dims[2] = {0, 0};
    leer_nivel_dim("niveles/nivel1.txt", dims);
    
    int tamNivel = dims[0] * dims[1];
    int nivel[ tamNivel ];
    leer_nivel("niveles/nivel1.txt", nivel, dims);

    /// Estado inicial

    int numCajas = 0;
    int numSensores = 0;
    Caja cajas[10];
    Sensor sensores[10];

    int cornerX = screenWidth / 2 - (dims[0]*tamCelda)/2;
    int cornerY = screenHeight / 2 - (dims[1]*tamCelda)/2;

    for (int i = 0; i < dims[0]; i++)
    {
        for (int j = 0; j < dims[1]; j++)
        {
            int casilla = nivel[i*dims[0]+j];

            switch (casilla)
            {
            case 0:
                personaje.casillaX = j;
                personaje.casillaY = i;
                personaje.posicion = (Vector2) { cornerX + j*tamCelda, cornerY + i*tamCelda };
                nivel[i*dims[0]+j] = 1;
                break;
            
            case 2: 
                cajas[numCajas].casillaX = j;
                cajas[numCajas].casillaY = i;
                cajas[numCajas].posicion = (Vector2) { cornerX + j*tamCelda, cornerY + i*tamCelda};
                cajas[numCajas].textura = caja;
                numCajas++;
                break;

            case 3: 
                sensores[numSensores].casillaX = j;
                sensores[numSensores].casillaY = i;
                sensores[numSensores].posicion = (Vector2) { cornerX + j*tamCelda, cornerY + i*tamCelda};
                sensores[numSensores].textura = sensor;
                numSensores++;
                nivel[i*dims[0]+j] = 1;
                break;

            default:
                break;
            }
        }
        
    }
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_RIGHT) && personaje.casillaX + 1 < dims[0]) {
            int indice = matrizAArreglo(dims[0], personaje.casillaX + 1, personaje.casillaY);
            int proxCasilla = nivel[indice];
            if (proxCasilla != -1) {

                if (proxCasilla == 2) {
                    bool cajaMovida = false;
                    for (int i = 0; i < numCajas; i++)
                    {
                        Caja *cajaDatos = &cajas[i];
                        if (cajaDatos->casillaX == (personaje.casillaX + 1) && cajaDatos->casillaY == personaje.casillaY) {
                            cajaMovida = moverCaja(cajaDatos->casillaX + 1, cajaDatos->casillaY, cajaDatos, nivel, dims);
                            break;
                        }
                    }

                    if (cajaMovida) {
                        personaje.casillaX = personaje.casillaX + 1;
                    }
                } else {
                    personaje.casillaX = personaje.casillaX + 1;
                }
            } 
            
        }

        if (IsKeyPressed(KEY_LEFT) && personaje.casillaX - 1 >= 0) {
            int indice = matrizAArreglo(dims[0], personaje.casillaX - 1, personaje.casillaY);
            int proxCasilla = nivel[indice];
            if (proxCasilla != -1) {
                if (proxCasilla == 2) {
                    bool cajaMovida = false;
                    for (int i = 0; i < numCajas; i++)
                    {
                        Caja *cajaDatos = &cajas[i];
                        if (cajaDatos->casillaX == (personaje.casillaX - 1) && cajaDatos->casillaY == personaje.casillaY) {
                            cajaMovida = moverCaja(cajaDatos->casillaX - 1, cajaDatos->casillaY, cajaDatos, nivel, dims);
                            break;
                        }
                    }

                    if (cajaMovida) {
                        personaje.casillaX = personaje.casillaX - 1;
                    }
                } else {
                    personaje.casillaX = personaje.casillaX - 1;
                }
            }
        } 

        if (IsKeyPressed(KEY_UP) && personaje.casillaY - 1 >= 0) {
            int indice = matrizAArreglo(dims[0], personaje.casillaX, personaje.casillaY - 1);
            int proxCasilla = nivel[indice];
            if (proxCasilla != -1) {
                if (proxCasilla == 2) {
                    bool cajaMovida = false;
                    for (int i = 0; i < numCajas; i++)
                    {
                        Caja *cajaDatos = &cajas[i];
                        if (cajaDatos->casillaX == personaje.casillaX && cajaDatos->casillaY == (personaje.casillaY - 1)) {
                            cajaMovida = moverCaja(cajaDatos->casillaX, (cajaDatos->casillaY - 1), cajaDatos, nivel, dims);
                            break;
                        }
                    }
                    if (cajaMovida) {
                        personaje.casillaY = personaje.casillaY - 1;
                    }
                } else {
                    personaje.casillaY = personaje.casillaY - 1;
                }
            }
        }
            
        if (IsKeyPressed(KEY_DOWN) && personaje.casillaY + 1 < dims[1]) {
            int indice = matrizAArreglo(dims[0], personaje.casillaX, personaje.casillaY + 1);
            int proxCasilla = nivel[indice];
            if (proxCasilla != -1) {
                if (proxCasilla == 2) {
                    bool cajaMovida = false;
                    for (int i = 0; i < numCajas; i++)
                    {
                        Caja *cajaDatos = &cajas[i];
                        if (cajaDatos->casillaX == personaje.casillaX && cajaDatos->casillaY == (personaje.casillaY + 1)) {
                            cajaMovida = moverCaja(cajaDatos->casillaX, (cajaDatos->casillaY + 1), cajaDatos, nivel, dims);
                            break;
                        }
                    }
                    if (cajaMovida) {
                        personaje.casillaY = personaje.casillaY + 1;
                    }
                } else {
                    personaje.casillaY = personaje.casillaY + 1;
                }
                
            }
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        ClearBackground(RAYWHITE);

            for (int i = 0; i < dims[0]; i++) {
                for (int j = 0; j < dims[1]; j++)
                {
                    int casilla = nivel[i*dims[0]+j];
                    DrawTexture(piso, cornerX + tamCelda*j, cornerY + tamCelda*i, WHITE);
                    switch (casilla)
                    {
                    case -1:
                        DrawTexture(pared, cornerX + tamCelda*j, cornerY + tamCelda*i, WHITE);
                        break;

                    default:
                        break;
                    }
                }
            }

            for (int i = 0; i < numCajas; i++)
            {
                Caja cajaDatos = cajas[i];
                DrawTexture(cajaDatos.textura, cornerX + tamCelda*cajaDatos.casillaX, cornerY + tamCelda*cajaDatos.casillaY, WHITE);
            }

            for (int i = 0; i < numSensores; i++)
            {
                Sensor sensorDatos = sensores[i];
                DrawTexture(sensorDatos.textura, sensorDatos.posicion.x, sensorDatos.posicion.y, WHITE);
            }
            

            DrawTexture(personaje.textura, cornerX + tamCelda*personaje.casillaX, cornerY + tamCelda*personaje.casillaY, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(personaje.textura);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}