search_path=$1
specific_str=$2
is_debug=$3

if (($#<3))
then
    echo -e "Usage: \n $0 search_path specific_str is_debug" && exit;
fi


echo -e "\n"
echo "search_path=$1"
echo "specific_str=$2"
echo "is_debug=$3"



echo -e "\n==> before delete \n"
echo -e "The file_name with specific_str number = "
find $search_path -name "*${specific_str}*" | wc -l


echo -e "\n deleteing ......\n"

for f in `find $search_path -name "*${specific_str}*"`;
do
    if ((${is_debug}));
    then
        echo -e "is_debug: \n${f}"
        break;
    else
        rm -rf $f
       #echo -e "rm -rf ....\n ${f}"
       #break;
    fi;
done;



echo -e "\n==> after delete \n"
echo -e "The file_name with specific_str number = "
find $search_path -name "*${specific_str}*" | wc -l

