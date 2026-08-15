
import turtle
import random
import time

# 初始化设置
WIDTH, HEIGHT = 600, 400
DELAY = 100  # 毫秒
GRID_SIZE = 20

# 初始化游戏窗口
window = turtle.Screen()
window.title("贪吃蛇游戏")
window.bgcolor("white")
window.setup(WIDTH, HEIGHT)
window.tracer(0)  # 关闭自动刷新

# 创建蛇头
snake_head = turtle.Turtle()
snake_head.shape("square")
snake_head.color("black")
snake_head.penup()
snake_head.goto(0, 0)
snake_head.direction = "stop"

# 蛇身初始两格
snake_body = []
for i in range(1, -1, -1):
    segment = turtle.Turtle()
    segment.shape("square")
    segment.color("green")
    segment.penup()
    segment.goto(0, -i * GRID_SIZE)
    snake_body.append(segment)

# 创建苹果
apple = turtle.Turtle()
apple.shape("circle")
apple.color("red")
apple.penup()
apple.goto(100, 100)

# 分数显示
score = 0
score_display = turtle.Turtle()
score_display.speed(0)
score_display.color("black")
score_display.penup()
score_display.hideturtle()
score_display.goto(0, HEIGHT//2 - 40)
score_display.write(f"分数: {score}", align="center", font=("Arial", 24))

# 移动函数
def move():
    if snake_head.direction == "up":
        y = snake_head.ycor()
        snake_head.sety(y + GRID_SIZE)
    elif snake_head.direction == "down":
        y = snake_head.ycor()
        snake_head.sety(y - GRID_SIZE)
    elif snake_head.direction == "left":
        x = snake_head.xcor()
        snake_head.setx(x - GRID_SIZE)
    elif snake_head.direction == "right":
        x = snake_head.xcor()
        snake_head.setx(x + GRID_SIZE)

# 方向控制
def go_up():
    if snake_head.direction != "down":
        snake_head.direction = "up"

def go_down():
    if snake_head.direction != "up":
        snake_head.direction = "down"

def go_left():
    if snake_head.direction != "right":
        snake_head.direction = "left"

def go_right():
    if snake_head.direction != "left":
        snake_head.direction = "right"

# 键盘绑定
window.listen()
window.onkeypress(go_up, "Up")
window.onkeypress(go_down, "Down")
window.onkeypress(go_left, "Left")
window.onkeypress(go_right, "Right")

# 主游戏循环
while True:
    window.update()
    
    # 边界检测（穿墙）
    if snake_head.xcor() > WIDTH//2:
        snake_head.setx(-WIDTH//2)
    elif snake_head.xcor() < -WIDTH//2:
        snake_head.setx(WIDTH//2)
    elif snake_head.ycor() > HEIGHT//2:
        snake_head.sety(-HEIGHT//2)
    elif snake_head.ycor() < -HEIGHT//2:
        snake_head.sety(HEIGHT//2)
    
    # 检测是否吃到苹果
    if snake_head.distance(apple) < GRID_SIZE:
        # 移动苹果到随机位置
        x = random.randint(-WIDTH//2 + GRID_SIZE, WIDTH//2 - GRID_SIZE)
        y = random.randint(-HEIGHT//2 + GRID_SIZE, HEIGHT//2 - GRID_SIZE)
        apple.goto(x, y)
        
        # 增加蛇身
        new_segment = turtle.Turtle()
        new_segment.shape("square")
        new_segment.color("green")
        new_segment.penup()
        snake_body.append(new_segment)
        
        # 增加分数
        score += 10
        score_display.clear()
        score_display.write(f"分数: {score}", align="center", font=("Arial", 24))
    
    # 移动蛇身
    for i in range(len(snake_body)-1, 0, -1):
        x = snake_body[i-1].xcor()
        y = snake_body[i-1].ycor()
        snake_body[i].goto(x, y)
    
    if len(snake_body) > 0:
        x = snake_head.xcor()
        y = snake_head.ycor()
        snake_body[0].goto(x, y)
    
    move()
    
    # 检测是否撞到自己
    for segment in snake_body:
        if segment.distance(snake_head) < GRID_SIZE//2:
            time.sleep(1)
            snake_head.goto(0, 0)
            snake_head.direction = "stop"
            for seg in snake_body:
                seg.goto(1000, 1000)  # 移出屏幕
            snake_body.clear()
            score = 0
            score_display.clear()
            score_display.write(f"分数: {score}", align="center", font=("Arial", 24))
    
    time.sleep(DELAY / 1000)

window.mainloop()
