//	按照置信度将所有的bbox升序排列（或者降序也行，只是后面的操作都相应改一下）作为一个set，然后：
//	选取set的最后一个bbox，并将该bbox加入pick集合
//	将set中该bbox之前的所有bbox与其计算overlap，将那些overlap大于指定threshold的bbox（包括该bbox自己）从set中删除，更新set
//	回到2，直到set中无元素。
//	返回pick集合，作为NMS之后得到的结果


#include<vector>
#include<assert.h>
#include<algorithm>
#include<utility>
#include"../utils/utils.hpp"


static bool my_comp(pair<vector<int>,float> a,  pair<vector<int>,float> b){
	return a.second < b.second;
}


static bool my_comp_for_cv(pair<cv::Rect,float> a,  pair<cv::Rect, float> b){
	return a.second < b.second;
}



vector<vector<int>> nms(vector<vector<int>> boxes_yxyx, vector<float>scores,  float IOU_min){
    //  [y_top, x_left, y_down, x_right] 
    //  scores_min != IOU_min
	assert(boxes_yxyx.size() > 0 && boxes_yxyx.size() == scores.size());
	assert(boxes_yxyx[0].size() == 4);

    vector<pair<vector<int>, float>> bboxes_scores;
    for(int i=0; i<boxes_yxyx.size(); i++){
        bboxes_scores.push_back(make_pair(boxes_yxyx[i], scores[i]));
    }
    //  1.sort the boxes_yxyx by confidence_scores
	sort(bboxes_scores.begin(), bboxes_scores.end(), my_comp);
    for(int i=0; i<boxes_yxyx.size(); i++){
        boxes_yxyx[i] = bboxes_scores[i].first;
    }
    vector<vector<int>>  pickes;
    while(!boxes_yxyx.empty()){
        
        //cout<<"pickes.size() = "<<pickes.size()<<endl;
        //2.    push_back the last element to the pickes;
        vector<int> pick = boxes_yxyx.back();
        pickes.push_back(pick); boxes_yxyx.pop_back();

        //3.    compute the overlap and just remain the IOU < IOU_min boxes;    and remain the sorting by scores
        vector<vector<int>> next_boxes_yxyx;
        for(auto bbox: boxes_yxyx){
            float y1 = min(bbox[0], pick[0]);
            float x1 = max(bbox[1], pick[1]);
            float y2 = max(bbox[2], pick[2]);
            float x2 = min(bbox[3], pick[3]);
            //  print_vec(bbox, "bbox = ");
            float S_inter = (x2 - x1) * (y1 - y2);
            //float S_outer = (bbox[3] - bbox[1])*(bbox[0] - bbox[2]) + (pick[3] - pick[1])*(pick[0] - pick[2]) + S_inter;
            float S_outer = (bbox[3] - bbox[1])*(bbox[0] - bbox[2]) + (pick[3] - pick[1])*(pick[0] - pick[2]) - S_inter;
            if(S_inter <=0 ||  S_inter / S_outer < IOU_min){
                next_boxes_yxyx.push_back(bbox);
            }
        }
        boxes_yxyx = next_boxes_yxyx;
    }
    return pickes;
}



vector<cv::Rect> nms_for_opencv(vector<cv::Rect> boxes_rec, vector<float>scores,  float IOU_min){
	assert(boxes_rec.size() > 0 && boxes_rec.size() == scores.size());

    vector<pair<cv::Rect, float>> bboxes_scores;
    for(int i=0; i<boxes_rec.size(); i++){
        bboxes_scores.push_back(make_pair(boxes_rec[i], scores[i]));
    }
    //  1.sort the boxes_rec by confidence_scores
	sort(bboxes_scores.begin(), bboxes_scores.end(), my_comp_for_cv);
    for(int i=0; i<boxes_rec.size(); i++){
        boxes_rec[i] = bboxes_scores[i].first;
    }
    vector<cv::Rect>  pickes;
    while(!boxes_rec.empty()){
        //cout<<"pickes.size() = "<<pickes.size()<<endl;
        //2.    push_back the last element to the pickes;
        cv::Rect pk = boxes_rec.back();
        //x1_y1_x2_y2
        vector<int> pick = {pk.x, pk.y,  pk.x + pk.width,  pk.y + pk.height };
        pickes.push_back(pk); boxes_rec.pop_back();

        //3.    compute the overlap and just remain the IOU < IOU_min boxes;    and remain the sorting by scores
        vector<cv::Rect> next_boxes_rec;
        for(auto bb: boxes_rec){
            // x1_y1_x2_y2
            vector<int> bbox = {bb.x, bb.y, bb.x + bb.width, bb.y + bb.height};
            float x1 = max(bbox[0], pick[0]);
            float y1 = max(bbox[1], pick[1]);
            float x2 = min(bbox[2], pick[2]);
            float y2 = min(bbox[3], pick[3]);
            //  print_vec(bbox, "bbox = ");
            float S_inter = (x2 - x1) * (y2 - y1);
            float S_outer = (bbox[3] - bbox[1])*(bbox[2] - bbox[0]) + (pick[3] - pick[1])*(pick[2] - pick[0]) - S_inter;
            if(S_inter <=0 ||  1.0* S_inter / S_outer < IOU_min){
                next_boxes_rec.push_back(bb);
            }
        }
        boxes_rec = next_boxes_rec;
    }
    return pickes;
}


















int main(){
    // y2_x1_y1_x2
    vector<vector<int>> Faked_bboxes_yxyx = {   {21, 10,  12, 12},  {25, 5,  3, 15}, {27, 5, 10, 15}, {20, 5,  1, 15}, 
                                                {21, 15,  1,  30},  {26, 6,  6, 40}, {24, 7, 3,  35}, {30, 11, 0, 56}};


    vector<cv::Rect> Faked_bboxes_Rect;
    for(auto vf: Faked_bboxes_yxyx){
        //cv::Rect rec(vf[1], vf[0], vf[3] - vf[1], vf[2] - vf[0]);
        cv::Rect rec(vf[1], vf[2], abs(vf[3] - vf[1]), abs(vf[2] - vf[0]));
        Faked_bboxes_Rect.push_back(rec);
    }
    


    vector<float> scores = {0.5, 0.3, 1, 0.8, 0.2, 0.14, 1, 0.99};
    float IOU_min = 0.24;





    vector<vector<int>>   pickes      =  nms(Faked_bboxes_yxyx, scores, IOU_min);
    vector<cv::Rect>         pickes_rec  =  nms_for_opencv(Faked_bboxes_Rect, scores, IOU_min);




    cout<<"bboxes = "<<endl;
    for(auto vec: Faked_bboxes_yxyx){
        print_vec(vec);    
        cout<<",";
    }
    print_vec(scores, "scores = ");



    cout<<endl<<"pickes = "<<endl;
    for (auto p: pickes){
        print_vec(p);
    }

    cout<<endl<<"pickes_rec = "<<endl;
    for (auto p: pickes_rec){
        vector<int> pv = {p.y, p.x, p.y + p.height, p.x + p.width};
        print_vec(pv);
    }


}
