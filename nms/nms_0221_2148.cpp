#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Bbox {
    int x1;
    int y1;
    int x2;
    int y2;
    float score;
    Bbox(int x1_, int y1_, int x2_, int y2_, float s):
	x1(x1_), y1(y1_), x2(x2_), y2(y2_), score(s) {};
};

float iou(Bbox box1, Bbox box2) {
    float area1 = (box1.x2 - box1.x1 + 1) * (box1.y2 - box1.y1 + 1);
    float area2 = (box2.x2 - box2.x1 + 1) * (box2.y2 - box2.y1 + 1);

    int x11 = std::max(box1.x1, box2.x1);
    int y11 = std::max(box1.y1, box2.y1);
    int x22 = std::min(box1.x2, box2.x2);
    int y22 = std::min(box1.y2, box2.y2);
    float intersection = (x22 - x11 + 1) * (y22 - y11 + 1);

    return intersection / (area1 + area2 - intersection);
}

std::vector<Bbox> nms(std::vector<Bbox> &vecBbox, float threshold) {
    auto cmpScore = [](Bbox box1, Bbox box2) {
	return box1.score < box2.score; // 升序排列, 令score最大的box在vector末端
    };
    std::sort(vecBbox.begin(), vecBbox.end(), cmpScore);

    std::vector<Bbox> pickedBbox;
    while (vecBbox.size() > 0) {
        pickedBbox.emplace_back(vecBbox.back());
        vecBbox.pop_back();
        for (size_t i = 0; i < vecBbox.size(); i++) {
            if (iou(pickedBbox.back(), vecBbox[i]) >= threshold) {
                vecBbox.erase(vecBbox.begin() + i);
            }
        }
    }
    return pickedBbox;
}

int main() {
    std::vector<Bbox> vecBbox;
    /// y2_x1_y1_x2
    vector<vector<int>> Faked_bboxes_yxyx = {   {21, 10,  12, 12},  {25, 5,  3, 15}, {27, 5, 10, 15}, {20, 5,  1, 15}, 
                                                  {21, 15,  1,  30},  {26, 6,  6, 40}, {24, 7, 3,  35}, {30, 11, 0, 56}};



    vector<float> scores = {0.5, 0.3, 1, 0.8, 0.2, 0.14, 1, 0.99};

    for(int i=0; i<scores.size(); i++){
//        vecBbox.emplace_back(Bbox(Faked_bboxes_yxyx[i][1], Faked_bboxes_yxyx[i][2], 
//                                  Faked_bboxes_yxyx[i][3], Faked_bboxes_yxyx[i][0],
//                                  scores[i]));
        vecBbox.emplace_back(Bbox(Faked_bboxes_yxyx[i][0], Faked_bboxes_yxyx[i][1], 
                                  Faked_bboxes_yxyx[i][2], Faked_bboxes_yxyx[i][3],
                                  scores[i]));
    }


    //  vecBbox.emplace_back(Bbox(187, 82, 337, 317, 0.9));
    //  vecBbox.emplace_back(Bbox(150, 67, 305, 282, 0.75));
    //  vecBbox.emplace_back(Bbox(246, 121, 368, 304, 0.8));

    auto pickedBbox = nms(vecBbox, 0.1);

    for (auto box : pickedBbox) {
	std::cout << box.x1 << ", " <<
		box.y1 << ", " <<
		box.x2 << ", " <<
		box.y2 << ", " <<
		box.score << std::endl;
    }
    return 0;
}
