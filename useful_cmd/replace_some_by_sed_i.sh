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




echo "==> before sed "
grep -rn "${old_str}" ${search_path}

echo -e "\n\n sed -i ......"
sed -i "s|${old_str}|${new_str}|g" $(grep -rl "${old_str}" ${search_path})
echo -e "\n\n"

echo "==> after sed "
grep -rn "${old_str}" ${search_path}
