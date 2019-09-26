search_path=$1

if (($#<1))
then
    echo -e "Usage: \n $0 search_path " && exit;
fi


echo -e "\nsearch_path=$1"

echo -e "\n"
for f in `ls $search_path`;
do
num=`cat $search_path/$f | wc -l`;
echo -e "$num  $f";
done;


