#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

double IOU(const Rect& r1, const Rect& r2)
{
    int x1 = std::max(r1.x, r2.x);
    int y1 = std::max(r1.y, r2.y);
    int x2 = std::min(r1.x+r1.width, r2.x+r2.width);
    int y2 = std::min(r1.y+r1.height, r2.y+r2.height);
    int w = std::max(0, (x2-x1+1));
    int h = std::max(0, (y2-y1+1));
    double inter = w * h;
    double o = inter / (r1.area() + r2.area() - inter);
    return (o >= 0) ? o : 0;
}

void nms(vector<Rect>& proposals, const double nms_threshold)
{
    vector<int> scores;
    for(auto i : proposals) scores.push_back(i.area());

    vector<int> index;
    for(int i = 0; i < scores.size(); ++i){
        index.push_back(i);
    }

    sort(index.begin(), index.end(), [&](int a, int b){
        return scores[a] > scores[b];
    }); 

    vector<bool> del(scores.size(), false);
    for(size_t i = 0; i < index.size(); i++){
        if( !del[index[i]]){
            for(size_t j = i+1; j < index.size(); j++){
                if(IOU(proposals[index[i]], proposals[index[j]]) > nms_threshold){
                    del[index[j]] = true;
                }
            }
        }
    }

    vector<Rect> new_proposals;
    for(const auto i : index){
        if(!del[i]) new_proposals.push_back(proposals[i]);
    }
    proposals = new_proposals;
}

void test_nms()
{

    nms(proposals, 0.2);
}
int main()
{
    test_nms();
    return 0;
}
