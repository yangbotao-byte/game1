#include"allinclude.h"
#include<algorithm>
void drawFlames();

#define MAXN 100
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 680

struct Node {
    int id, x, y;
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};

vector<Node> nodes;
vector<pair<int, int> > graph[MAXN];
vector<Edge> allEdges;
vector<Edge> mstEdges; // 当前MST的边
float pulse = 0;
bool increasing = true;
bool showMST = false;

struct Flame {
    int x, y, life;
};
vector<Flame> flames;

int fa[MAXN];
int find(int x) {
    if (fa[x] == x) {
        return x;
    }
    else {
        fa[x] = find(fa[x]);  // 路径压缩
        return fa[x];
    }
}

void addEdge(int u, int v, int w) {
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
    allEdges.push_back({ u, v, w });
}

void kruskal(int start, int end) {
    for (int i = 0; i < MAXN; ++i) fa[i] = i;
    sort(allEdges.begin(), allEdges.end());
    mstEdges.clear();

    for (Edge& e : allEdges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            fa[fu] = fv;
            mstEdges.push_back(e);
        }
    }
    showMST = true;
}

vector<int> dijkstra(int start, int end) {
    const int INF = 1e9;
    vector<int> dist(nodes.size(), INF);
    vector<int> prev(nodes.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int d = top.first, u = top.second;
        if (d > dist[u]) continue;

        for (int i = 0; i < (int)graph[u].size(); ++i) {
            int v = graph[u][i].first;
            int w = graph[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int getClickedNode(int mx, int my) {
    for (int i = 0; i < (int)nodes.size(); ++i) {
        int dx = mx - nodes[i].x;
        int dy = my - nodes[i].y;
        if (sqrt(dx * dx + dy * dy) < 25)
            return nodes[i].id;
    }
    return -1;
}

void drawMST() {
    int glow = 100 + int(80 * pulse);
    setlinecolor(RGB(glow, glow, 255));
    setlinestyle(PS_SOLID, 3);
    for (Edge& e : mstEdges) {
        Node a = nodes[e.u], b = nodes[e.v];
        line(a.x, a.y, b.x, b.y);
    }
    setlinestyle(PS_SOLID, 1);
    setlinecolor(WHITE);
}

void drawMap() {
    setbkcolor(RGB(20, 20, 30));
    cleardevice();
    if (showMST) drawMST();

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 1);
    for (int u = 0; u < (int)nodes.size(); ++u) {
        for (int i = 0; i < (int)graph[u].size(); ++i) {
            int v = graph[u][i].first;
            line(nodes[u].x, nodes[u].y, nodes[v].x, nodes[v].y);
        }
    }

    int baseColor = 50 + int(pulse * 100);
    settextcolor(WHITE);
    settextstyle(16, 0, _T("Consolas"));
    for (int i = 0; i < (int)nodes.size(); ++i) {
        setfillcolor(RGB(baseColor, baseColor, baseColor));
        fillcircle(nodes[i].x, nodes[i].y, 15);
        TCHAR idStr[10];
        _stprintf(idStr, _T("%d"), nodes[i].id);
        outtextxy(nodes[i].x - 6, nodes[i].y - 8, idStr);
    }
}

void drawDot(int x, int y) {
    setfillcolor(RGB(200, 200, 255));
    setlinecolor(BLACK);
    fillcircle(x, y, 10);
    setlinecolor(RGB(150, 150, 255));
    circle(x, y, 12);
}

void moveAlongPath(const vector<int>& path) {
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        int u = path[i], v = path[i + 1];
        int x1 = nodes[u].x, y1 = nodes[u].y;
        int x2 = nodes[v].x, y2 = nodes[v].y;
        float dx = (x2 - x1) / 50.0f;
        float dy = (y2 - y1) / 50.0f;
        float x = x1, y = y1;

        for (int step = 0; step <= 50; ++step) {
            drawMap();
            drawDot((int)x, (int)y);
            drawFlames();
            FlushBatchDraw();
            x += dx;
            y += dy;
            Sleep(15);
        }
    }
}

void updatePulse() {
    if (increasing) {
        pulse += 0.02f;
        if (pulse >= 1.0f) increasing = false;
    }
    else {
        pulse -= 0.02f;
        if (pulse <= 0.2f) increasing = true;
    }
}

void initGraph() {
    nodes.clear();
    allEdges.clear();
    for (int i = 0; i < MAXN; ++i) graph[i].clear();

    nodes.push_back({ 0, 200, 100 });
    nodes.push_back({ 1, 400, 200 });
    nodes.push_back({ 2, 600, 100 });
    nodes.push_back({ 3, 800, 250 });
    nodes.push_back({ 4, 650, 400 });
    nodes.push_back({ 5, 350, 350 });
    nodes.push_back({ 6, 1000, 150 });
    nodes.push_back({ 7, 1150, 300 });
    nodes.push_back({ 8, 1100, 500 });
    nodes.push_back({ 9, 900, 450 });

    addEdge(0, 1, 10);
    addEdge(1, 2, 10);
    addEdge(1, 5, 15);
    addEdge(2, 3, 10);
    addEdge(3, 4, 10);
    addEdge(4, 5, 10);
    addEdge(0, 5, 25);
    addEdge(2, 6, 20);
    addEdge(6, 7, 10);
    addEdge(7, 8, 15);
    addEdge(8, 9, 10);
    addEdge(4, 9, 20);
}

void drawFlames() {
    for (int i = 0; i < (int)flames.size(); ++i) {
        setfillcolor(RGB(255, 100 + rand() % 100, 0));
        fillcircle(flames[i].x, flames[i].y, 3);
        flames[i].y -= 1 + rand() % 3;
        flames[i].life--;
    }
    flames.erase(remove_if(flames.begin(), flames.end(), [](Flame f) { return f.life <= 0; }), flames.end());
    for (int i = 0; i < 10; ++i) {
        Flame f = { rand() % SCREEN_WIDTH, SCREEN_HEIGHT - 10, 20 + rand() % 20 };
        flames.push_back(f);
    }
}

int mymap() {

    mciSendString("open ./music\\begin.mp3", 0, 0, 0);
    mciSendString("play ./music\\begin.mp3 repeat", 0, 0, 0);
    srand((unsigned)time(0));
    BeginBatchDraw();

    initGraph();

    int start = 0;
    while (1) {
        drawMap();
        drawDot(nodes[start].x, nodes[start].y);
        drawFlames();
        updatePulse();

        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int end = getClickedNode(msg.x, msg.y);
                if (end != -1 && end != start) {
                    vector<int> path = dijkstra(start, end);
                    moveAlongPath(path);
                    start = end;
                    showMST = false;
                }
            }
            else if (msg.uMsg == WM_RBUTTONDOWN) {
                int target = getClickedNode(msg.x, msg.y);
                if (target != -1 && target != start) {
                    kruskal(start, target);
                }
            }
        }

        if (_kbhit()) {
            int ch = _getch();
            if (ch == 13) { // Enter 键
                if(start != 0){
                EndBatchDraw(); // 结束绘制
                return start;   // 返回当前所在节点编号
                }
            }
        }

        FlushBatchDraw();
        Sleep(20);
    }
    EndBatchDraw();
    return 0;
}
