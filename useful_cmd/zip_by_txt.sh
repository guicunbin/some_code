txt_path=$1
zip_name=$2

if (($#<2))
then
    echo -e "Usage: \n $0 txt_path zip_name" && exit;
fi


echo -e "txt_path=$1"
echo -e "zip_name=$2"


cat ${txt_path} | zip -@ ${zip_name}.zip


