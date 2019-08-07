#coding: utf-8
keywords=$1
limit=$2
output_directory=$3
image_directory=$4


if (($#<4))
then
    echo -e "Usage: \n $0 keywords limit output_directory image_directory" && exit;
fi

echo "keywords=$1"
echo "limit=$2"
echo "output_directory=$3"
echo "image_directory=$4"




pip install google_images_download -i https://pypi.tuna.tsinghua.edu.cn/simple/ --user
googleimagesdownload \
    -k "$keywords" \
    -l $limit \
    -o $output_directory \
    -i $image_directory
