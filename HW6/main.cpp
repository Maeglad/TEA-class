#include <cstdlib>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

struct point{
    long long x,y;  
    struct point operator- (struct point b){
        struct point p;
        p.x = x - b.x;
        p.y = y - b.y;
        return p;
    }
};

struct PointComparator{
    bool operator() (struct point a, struct point b){
        if(a.x > b.x) return true;
        if(a.x < b.x) return false;
        if(a.y > b.y) return true;
        return false;
    } 
};

struct PointComparatorReverse{
    bool operator() (struct point a, struct point b){
        if(a.x < b.x) return true;
        if(a.x > b.x) return false;
        if(a.y < b.y) return true;
        return false;
    } 
};

long long cross(struct point a, struct point b){
    return (a.x*b.y - a.y*b.x);
    
}

int main(int argc, char** argv) {
    priority_queue<struct point, vector<struct point>, PointComparator> queue;
    vector<struct point> points, sorted;
    
    int n; 
    scanf("%d", &n);
    
    for(int i = 0; i < n; ++i){
        struct point p;
        int x, y;
        scanf("%d %d", &x, &y);
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    
    vector<struct point> upper, lower;
    for(int i = 0; i < points.size(); ++i){
        queue.push(points[i]);
    }
    while(queue.empty() == false){
        sorted.push_back(queue.top());
        queue.pop();
    }
    for(int i = 0; i < sorted.size(); ++i){
        struct point p = sorted[i];
        while((upper.size() > 1)&&(cross(upper[upper.size() - 1] - upper[upper.size() - 2], p - upper[upper.size() - 2]) >= 0)){
            upper.pop_back();
        }
        upper.push_back(p);
    }
    
    for(int i = sorted.size() -1; i >= 0; --i){
        struct point p = sorted[i];
        while((lower.size() > 1)&&(cross(lower[lower.size() - 1] - lower[lower.size() - 2], p - lower[lower.size() - 2]) >= 0)){
            lower.pop_back();
        }
        lower.push_back(p);
    }
    
    vector<struct point> hull;
    for(int i = 0; i < upper.size(); ++i){
        hull.push_back(upper[i]);
    }
    for(int i = 1; i < lower.size() -1; ++i){
        hull.push_back(lower[i]);
    }
    hull.push_back(upper[0]);
   
    /*
     * calculate area of convex hull
     * area = sum(||hull[i+1] x hull[i]||)/2 i=0..n-1
     */
    long long area = 0;
    for(int i = 0; i < hull.size() - 1; ++i){
        area += cross(hull[i+1], hull[i]);
    }
    area = abs(area);
    cout << area / 2;
    if((area % 2) == 0)cout << endl;
    else cout << ".5" << endl;    
    return 0;
}

