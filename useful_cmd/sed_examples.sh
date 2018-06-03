
sed -i "s|from_detection_checkpoint: true|from_detection_checkpoint: false|g" ${PATH_TO_YOUR_PIPELINE_CONFIG}

sed -i 's|fine_tune_checkpoint_type:  "detection"|from_detection_checkpoint: false|g' ${PATH_TO_YOUR_PIPELINE_CONFIG}



sed -i "s|"PATH_TO_BE_CONFIGURED/model.ckpt"|"${fine_tune_checkpoint}"|g" ${PATH_TO_YOUR_PIPELINE_CONFIG}
sed -i "s|PATH_TO_BE_CONFIGURED|"${PATH_TO_BE_CONFIGURED}"|g"  ${PATH_TO_YOUR_PIPELINE_CONFIG}
sed -i "s| num_steps:| #num_steps:|g" ${PATH_TO_YOUR_PIPELINE_CONFIG}
sed -i '/eval_config:.*/a\  metrics_set: "coco_detection_metrics"'  ${PATH_TO_YOUR_PIPELINE_CONFIG}




sed -i "s|utils_image|"Utils_Image"|g"  `grep -rl "utils_image"./*`

