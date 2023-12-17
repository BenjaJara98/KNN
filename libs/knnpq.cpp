#include "knnpq.hpp"
#include<unistd.h>

using namespace std;

class Quadrant
{
private:
    pair<int, int> S;
    pair<int, int> T;

    pair<int, int> min(pair<int, int> p1, pair<int, int> p2)
    {

        pair<int, int> point = make_pair(std::min(p1.first, p2.first), std::min(p1.second, p2.second));
        return point;
    }

    pair<int, int> max(pair<int, int> p1, pair<int, int> p2)
    {

        pair<int, int> point = make_pair(std::max(p1.first, p2.first), std::max(p1.second, p2.second));
        return point;
    }

public:
    Quadrant(){};
    ~Quadrant(){};

    Quadrant(pair<int, int> S, pair<int, int> T)
    {
        this->S = S;
        this->T = T;
    }

    pair<int, int> getS()
    {
        return S;
    }

    pair<int, int> getT()
    {
        return T;
    }

    bool Contains(pair<int, int> point)
    {
       return (S.first <= point.first) && point.first <= T.first && S.second <= point.second && point.second <= T.second;
    }

    void printQuad(){
        cout <<"   QUAD: "<< "(" << S.first << "," << S.second << ")" <<" - "<< "(" << T.first << "," << T.second << ")\n";
        return;
    }

};

struct knnpqElement
{

    int position;      // Position of the element in T:L
    Quadrant quadrant; // Quadrant of point
    int distance;      // Mindist
    int level;         // Level in tree of element

    knnpqElement(){};
    ~knnpqElement(){};
    knnpqElement(int _position, Quadrant _quadrant, int _distance, int _level)
    {
        position = _position;
        quadrant = _quadrant;
        distance = _distance;
        level = _level;
    };

    void printElement(){
        printf("---------ELEMENT---------\n");
        cout << "   POSITION: " << this->position << "\n"  << "   DISTANCE: " << this->distance<< "\n" << "   LEVEL: " << this->level << "\n";
        this->quadrant.printQuad();
    }
};

bool compMinHeap(knnpqElement A_element, knnpqElement B_element)
{
    int a = A_element.distance;
    int b = B_element.distance;
    return a > b;
};
bool compMaxHeap(knnpqElement A_element, knnpqElement B_element)
{
    int a = A_element.distance;
    int b = B_element.distance;
    return a < b;
};


int64_t knnpq::minDist(pair<int, int> point, Quadrant quadrant)
{

    int64_t R1 = 0;
    int64_t R2 = 0;

    if (quadrant.Contains(point))
    {
        return 0;
    }
    else
    {

        if (point.first < quadrant.getS().first)
        {
            R1 = quadrant.getS().first;
        }
        else
        {
            if (point.first > quadrant.getT().first)
            {
                R1 = quadrant.getT().first;
            }
            else
            {
                R1 = point.first;
            }
        }
    }

    if (point.second < quadrant.getS().second)
    {
        R2 = quadrant.getS().second;    
    }
    else
    {
        if (point.second > quadrant.getT().second)
        {
            R2 = quadrant.getT().second;
        }
        else
        {
            R2 = point.second;
        }
    }

    int64_t value1 = point.first - R1;
    int64_t value2 = point.second - R2;

    return llabs(value1 * value1) + llabs(value2 * value2);
}

vector<knnpqElement> knnpq::getChildrenOfElement(knnpqElement element, pair<int, int> point, uint max_level, bitRankW32Int *btl)
{

    int quad_x = 0;
    int quad_y = 0;

    pair<int, int> S = element.quadrant.getS();
    pair<int, int> T = element.quadrant.getT();

    /*int accumX = 0;
    int accumY = 0;*/

    vector<knnpqElement> childrens;

    uint childrenPosition = element.position == -1 ? 0 : rank1(btl, element.position) * pow(K, 2);
    uint nChildren = K * K;

    int secuence = (element.quadrant.getT().second - element.quadrant.getS().second) / K;

    Quadrant temp_quadrant;

    /*if (element.level > max_level)
    {

        accumX = S.first;
        accumY = T.second;
    }
    else
    {
        accumX = S.first;
        accumY = T.second - secuence;
    }*/

    quad_x = S.first;
    quad_y = S.second;

    for (int i = 0; i < nChildren; i++)
    {
        

        /*if (accumX > T.first)
        {
            accumY = accumY - secuence - 1;
            accumX = S.first;
        }*/

        if (isBitSet(btl, childrenPosition))
        {

            temp_quadrant = Quadrant(make_pair(quad_x, quad_y), make_pair(quad_x + secuence, quad_y + secuence));

            int64_t minD = minDist(point, temp_quadrant);
            //knnpqElement new_element = knnpqElement(rank1(btl, childrenPosition) * K * K, temp_quadrant, minD, element.level + 1);
            knnpqElement new_element = knnpqElement(childrenPosition, temp_quadrant, minD, element.level + 1);


            childrens.push_back(new_element);
        }

        quad_x = quad_x + secuence;

        if( (i+1)% K == 0){
            quad_x = S.first;
            quad_y = quad_y + secuence;
        }

        //accumX = accumX + secuence + 1;
        childrenPosition++;
    }

    return childrens;
};

vector<pair<int, int>> knnpq::knn(MREP *rep, int x, int y, int k)
{

    pair<int, int> point = make_pair(x, y);

    Quadrant quad = Quadrant(make_pair(0, 0), make_pair(rep->numberOfNodes, rep->numberOfNodes));

    vector<knnpqElement> cand, pqueue;
    make_heap(cand.begin(), cand.end(), compMaxHeap);
    make_heap(pqueue.begin(), pqueue.end(), compMinHeap);

    knnpqElement element = knnpqElement(-1, quad, minDist(point, quad), 0); // element in form (point, quad(Tree) ,dist(point q, Quad(Tree)),level in tree)
    vector<pair<int, int>> points;

    pqueue.push_back(element);

    while (pqueue.size() != 0)
    {

        element = pqueue.front();
        pop_heap(pqueue.begin(), pqueue.end(), compMinHeap);
        pqueue.pop_back();  

        if (cand.size() == k && element.distance >= cand.front().distance)
        {

            for(knnpqElement aux : cand){
                points.push_back(make_pair(aux.quadrant.getS().first, aux.quadrant.getS().second));
            }
                return points; // Need to return points in form vector<pair<int,int>>
        }

        bool isLeaf = false; // Element isLeaf?

        if (element.level > rep->maxLevel)
        { // Function to determine if element isLeaf #NEED TO TEST
            isLeaf = true;
        }

        if (isLeaf)
        {

            knnpqElement pointElement = element; // pointElement to work in cand queue   - Is the same as element and have the same parameters.

            // If to evaluate if cand is not full, we asign element to the heap.
            if (cand.size() < k)
            {
                cand.push_back(pointElement);
                push_heap(cand.begin(), cand.end(), compMaxHeap);
            }
            else
            {
                // If to evaluate if element has minor distance than the element with greater distance in candidates in priority queue
                if (element.distance < cand.front().distance)
                {
                    pop_heap(cand.begin(), cand.end(), compMaxHeap);
                    cand.pop_back();
                    cand.push_back(element);
                    push_heap(cand.begin(), cand.end(), compMaxHeap);
                }
            }
        }
        else
        {
            vector<knnpqElement> childrens = getChildrenOfElement(element, point, rep->maxLevel, rep->btl); // Function that returns vector of childrens of element

            for (knnpqElement aux_element : childrens)
            { // aux_element is the children of element
                int dist = aux_element.distance;
                if (cand.size() < k || dist < cand.front().distance)
                { // is cand size lower than k neighbors to search OR dist of children lower than distance of front element of cand
                    pqueue.push_back(aux_element);
                    push_heap(pqueue.begin(), pqueue.end(), compMinHeap); // Push the element to be evaluated
                }
            }
        }
    }

    for(knnpqElement aux : cand){
        points.push_back(make_pair(aux.quadrant.getS().first, aux.quadrant.getS().second));
    }
    return points; // Need to return all the points in form vector<pair<int,int>>
};