//	按照置信度将所有的bbox升序排列（或者降序也行，只是后面的操作都相应改一下）作为一个set，然后：
//	选取set的最后一个bbox，并将该bbox加入pick集合
//	将set中该bbox之前的所有bbox与其计算overlap，将那些overlap大于指定threshold的bbox（包括该bbox自己）从set中删除，更新set
//	回到2，直到set中无元素。
//	返回pick集合，作为NMS之后得到的结果


#include<vector>
#include<assert.h>
#include<algorithm>
#include<utility>
#include"../../utils/utils.hpp"


static bool my_comp(pair<vector<float>,float> a,  pair<vector<float>,float> b){
	return a.second < b.second;
}

vector<vector<float>> nms(vector<vector<float>> boxes_yxyx, vector<float>scores,  float IOU_min){
    //  [y_top, x_left, y_down, x_right] 
    //  scores_min != IOU_min
	assert(boxes_yxyx.size() > 0 && boxes_yxyx.size() == scores.size());
	assert(boxes_yxyx[0].size() == 4);

    vector<pair<vector<float>, float>> bboxes_scores;
    for(int i=0; i<boxes_yxyx.size(); i++){
        bboxes_scores.push_back(make_pair(boxes_yxyx[i], scores[i]));
    }
    //  1.sort the boxes_yxyx by confidence_scores
	sort(bboxes_scores.begin(), bboxes_scores.end(), my_comp);
    for(int i=0; i<boxes_yxyx.size(); i++){
        boxes_yxyx[i] = bboxes_scores[i].first;
    }
    vector<vector<float>>  pickes;
    while(!boxes_yxyx.empty()){
        
        //cout<<"pickes.size() = "<<pickes.size()<<endl;
        //2.    push_back the last element to the pickes;
        vector<float> pick = boxes_yxyx.back();
        pickes.push_back(pick); boxes_yxyx.pop_back();

        //3.    compute the overlap and just remain the IOU < IOU_min boxes;    and remain the sorting by scores
        vector<vector<float>> next_boxes_yxyx;
        for(auto bbox: boxes_yxyx){
            float y1 = min(bbox[0], pick[0]);
            float x1 = max(bbox[1], pick[1]);
            float y2 = max(bbox[2], pick[2]);
            float x2 = min(bbox[3], pick[3]);
            //  print_vec(bbox, "bbox = ");
            float S_inter = (x2 - x1) * (y1 - y2);
            float S_outer = (bbox[3] - bbox[1])*(bbox[0] - bbox[2]) + (pick[3] - pick[1])*(pick[0] - pick[2]) + S_inter;
            if(S_inter <=0 ||  S_inter / S_outer < IOU_min){
                next_boxes_yxyx.push_back(bbox);
            }
        }
        boxes_yxyx = next_boxes_yxyx;
    }
    return pickes;
}





int main(){
    vector<vector<float>> Faked_bboxes_yxyx = {   {2, 0,  1, 1},  {2, 0,  0, 1}, {2, 0.5, 1, 1}, {2, 0.5, 1, 1.5}, 
                                                  {2, 0.5,0, 3},  {2, 0.6,0, 4}, {2,0.7, 0,4.5}, {3, 1.1, 0, 5.6}};
    vector<float> scores = {0.5, 0.3, 1, 0.8, 0.2, 0.14, 1, 0.99};
    float IOU_min = 0.2;
    vector<vector<float>> pickes =  nms(Faked_bboxes_yxyx, scores, IOU_min);

    cout<<"bboxes = "<<endl;
    for(auto vec: Faked_bboxes_yxyx){
        print_vec(vec);    
        cout<<",";
    }
    print_vec(scores, "scores = ");



    cout<<endl<<"pickes = "<<endl;
    for (int i=0; i<pickes.size(); i++){
        print_vec(pickes[i]);
    }
}
