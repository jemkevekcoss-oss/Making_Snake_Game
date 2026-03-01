#include "ObjectClasses.h"
using namespace std;



Snake::Snake() {
    body = { Vector2{7,6},Vector2{6,6},Vector2{5,6} };
    direction = { 1,0 };
    addSegment = false;
    
    Image headImage = LoadImage("C:/SnakeGameWithRaylib/Images/SnakeHead.png");
    Image bodyImage = LoadImage("C:/SnakeGameWithRaylib/Images/snakeBody.png");
    Image tailImage = LoadImage("C:/SnakeGameWithRaylib/Images/snakeTail.png");
    ImageResize(&headImage, CellSize, CellSize);
    ImageResize(&bodyImage, CellSize, CellSize);
    ImageResize(&tailImage, CellSize, CellSize);
    
    headTexture = LoadTextureFromImage(headImage);
    bodyTexture = LoadTextureFromImage(bodyImage);
    tailTexture = LoadTextureFromImage(tailImage);

    UnloadImage(headImage); UnloadImage(bodyImage); UnloadImage(tailImage);


}
Snake::~Snake() {
    UnloadTexture(headTexture);
    UnloadTexture(bodyTexture);
    UnloadTexture(tailTexture);
}

void Snake::Draw() {
    for (unsigned int i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        //Rectangle segment = Rectangle{ offset + x * CellSize,offset + y * CellSize,(float)CellSize,(float)CellSize }
        //DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, darkgreen);
        //DrawRectangleRounded(segment, 0.5, 6, darkgreen);
        
        if(i == 0) 
            DrawTexture(headTexture, (float)offset + x * CellSize, (float)offset + y * CellSize, WHITE);
        else if(i == body.size()-1) 
            DrawTexture(tailTexture, (float)offset + x * CellSize, (float)offset + y * CellSize, WHITE);
        else 
            DrawTexture(bodyTexture, (float)offset + x * CellSize, (float)offset + y * CellSize, WHITE);
    }
}



void Snake::Update() {
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment) {
        addSegment = false;
    }
    else {
        body.pop_back();
    }
}

void Snake::Reset() {
    //KHởi tạo trạng thái, vị trí rắn ban đầu
    body = { Vector2{7,6},Vector2{6,6},Vector2{5,6} };
    direction = { 1,0 };
}

Food::Food(deque <Vector2> SnakeBody) {
    Image image = LoadImage("C:/SnakeGameWithRaylib/Images/Food.png");

    // Ép ảnh về đúng kích thước
    ImageResize(&image, CellSize, CellSize);
    // Đẩy lên GPU
    texture = LoadTextureFromImage(image);
    // Giải phóng 
    UnloadImage(image);
    position = GenerateRandomPos(SnakeBody); //Vị trí đầu tiên của mồi

}

Food::~Food() {
    UnloadTexture(texture);
}

void Food::Draw() {

    DrawTexture(texture, (float)offset + position.x * CellSize, (float)offset + position.y * CellSize, WHITE);

}

Vector2 Food::GetRandomCell() {
    float x = GetRandomValue(0, CellCount - 1);
    float y = GetRandomValue(0, CellCount - 1);

    return Vector2{ x,y };
}

Vector2 Food::GenerateRandomPos(deque <Vector2> SnakeBody) {


    Vector2 pos = GetRandomCell();
    while (ElementOnDeque(pos, SnakeBody)) { //Truyền vào pos ko phải position
        pos = GetRandomCell();
    }
    return pos;
}


Game::Game() {
    InitAudioDevice();
    eatSound = LoadSound("C:/SnakeGameWithRaylib/Sounds/eat.mp3");
    wallColSound = LoadSound("C:/SnakeGameWithRaylib/Sounds/wall.mp3");
}
Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(wallColSound);
    CloseAudioDevice();

}


void Game::Draw() {
    snake.Draw();
    food.Draw();
}
void Game::Update() {
    if (running) {
        snake.Update();
        CheckCollisionwithFood();
        checkCollisionWithWalls();
        checkCollisionWithBody();
    }
}

void Game::CheckCollisionwithFood() {
    //if (snake.body[0] == food.position) food.position = food.GenerateRandomPos();
    if (Vector2Equals(snake.body[0], food.position)) {
        cout << "Eating food\n";
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        ++score;
        PlaySound(eatSound);

        //Vector2 segment = snake.body[snake.body.size() - 1];
        //snake.body.push_back(segment);
    }
}


void Game::GameOver() {
    cout << "Game Over!\n";
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(wallColSound);

}

void Game::checkCollisionWithWalls() { //////////////////////////////////////

    if (snake.body[0].x == CellCount || snake.body[0].x < 0) GameOver();
    if (snake.body[0].y == CellCount || snake.body[0].y < 0) GameOver();

}

void Game::checkCollisionWithBody() {
    //Snake without it's head
    deque <Vector2> headlessBody = snake.body;
    headlessBody.pop_front(); //erase snake's head
    if (ElementOnDeque(snake.body[0], headlessBody)) {
        GameOver();
    }
}
