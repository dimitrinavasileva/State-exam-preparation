#include<iostream>
#include<list>
#include <string>

using namespace std;

constexpr int N = 3;
int GameBoard[N][N] = { 
    {1, 0, 1},
    {0, 1, 2},
    {0, 0, 2} 
};

struct Point
{
    int x;
    int y;
    Point() : x(0) , y(0)
    { }
    Point(int x, int y) : x(x), y(y)
    {}

    string toString() const 
    {
        string res;
        res.append("(").append(x).append(",").append(y).append(")");
        return res;
    }
};

list<Point> adjacentPoints(const Point &p)
{
    list<Point> res;
    for (int i = p.x - 1; i <= p.x + 1; i++)
    {
        if (i >= 0 && i < N)
        {
            for (int j = p.y - 1; j <= p.y + 1; j++)
            {
                if (j >= 0 && j < N)
                {
                    res.push_front(Point{i, j});
                }
            }
        }
    }
    return res;
}

class GamePlayer
{
private:
    Point m_p;

public:
    GamePlayer(Point p) : m_p(p) {}
    virtual ~GamePlayer() {}
    
    Point getPosition() const { return m_p; }
    void setPosition(const Point &p) { m_p = p; }

    virtual list<Point> allowedMoves() const = 0;
    virtual string whatIAm() const = 0;
};

class Knight : public GamePlayer
{
public:
    Knight(Point p{0, 0}) : GamePlayer(p)
    { }

    virtual list<Point> allowedMoves() const override
    {
        list<Point> res;
        for (Point &adj: adjacentPoints(p))
        {
            if (GameBoard[adj.x][adj.y] == 0 && adj != p)
            {
                bool isThereFireNearby = false;
                for (Point &nearbyPoint: adjacentPoints(adj))
                {
                    if (GameBoard[adj.x][adj.y] == 1)
                    {
                        isThereFireNearby = true;
                    }
                }
                if (!isThereFireNearby)
                {
                    res.push_front(adj);
                }
            }
        }
        return res;
    }

    virtual string whatIAm() const override
    {
        return "Knight";
    }
    
};

class SeaMonster : public GamePlayer
{
public:
    SeaMonster(Point p{0, 0}) : GamePlayer(p)
    { }
    
    virtual list<Point> allowedMoves() const override
    {
        list<Point> res;
        
        for (int i = p.x - 1; i >= 0 && GameBoard[i][p.y] == 2; i--)
        {
            res.push_front(Point{i, p.y});
        }

        for (int i = p.x + 1; i < N && GameBoard[i][p.y] == 2; i++)
        {
            res.push_front(Point{i, p.y});
        }

        for (int j = p.y - 1; j >= 0 && GameBoard[p.x][j] == 2; j--)
        {
            res.push_front(Point{p.x, j});
        }

        for (int j = p.y + 1; j < N && GameBoard[p.x][j] == 2; j++)
        {
            res.push_front(Point{p.x, j});
        }

        return res;
    }
    
    virtual string whatIAm() const override
    {
        return "SeaMonster";
    }
};

bool isWar(GamePlayer* players[])
{
    for (GamePlayer* player : players)
    {
        list<Point> adjPoints = adjacentPoints(player->getPosition());
        bool isAttacked = false;
        for (GamePlayer* anotherPlayer : players)
        {
            for (Point &p : adjPoints)
            {
                if (anotherPlayer->getPosition() == p)
                {
                    isAttacked = true;
                    break;
                }
            }
        }
        if (!isAttacked)
        {
            return false;
        }
    }
    return true;
}

void allMoves(GamePlayer* players[])
{
    for (GamePlayer* player : players)
    {
        Point oldPoint = player->getPosition();
        for (Point &p : player->allowedMoves())
        {
            player->setPosition(p);
            if (isWar(players))
            {
                std::cout << player->whatIAm() << oldPoint.toString() << " -> " << p.toString() << "\n";
            }
        }
        player->setPosition(oldPoint);
    }
}

int main()
{
    
    Point p(1,3);
    Knight k(p);
    k.getPosition();
}