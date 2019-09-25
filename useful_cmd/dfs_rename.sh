search_path=$1
old_str=$2
new_str=$3

if (($#<3))
then
    echo -e "Usage: \n $0 search_path old_str new_str" && exit;
fi



echo "search_path=$1"
echo "old_str=$2"
echo "new_str=$3"




echo "==> before find + rename "
find ${search_path} -name "*${old_str}*" | head -2
find ${search_path} -name "*${old_str}*" | wc -l

echo -e "\n\n find + rename ......"
find ${search_path} -name "*${old_str}*" | rename "s|${old_str}|${new_str}|g"
echo -e "\n\n"

echo "==> after find + rename "
find ${search_path} -name "*${old_str}*" | head -2
find ${search_path} -name "*${old_str}*" | wc -l

