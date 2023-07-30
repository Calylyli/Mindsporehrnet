
if [[ $# != 2 ]]; then
    echo "Usage:"
    echo "sh do_infer.sh [DATA_PATH] [DATA_LST]"
    exit 1
fi

get_real_path(){
    if [ "${1:0:1}" == "/" ]; then
        echo "$1"
    else
        echo "$(realpath -m $PWD/$1)"
    fi
}

PATH1=$(get_real_path $1)
PATH2=$(get_real_path $2)

if [ ! -d $PATH1 ]
then
    echo "error: DATA_PATH=$PATH1 is not a directory."
    exit 1
fi

if [ ! -f $PATH2 ]
then
    echo "error: DATA_LST=$PATH2 is not a file."
    exit 1
fi

rm -rf ./inferResults
mkdir ./inferResults

echo "Inference results will be stored in ./inferResults/."

python3.7 main.py --pipeline="../data/config/hrnetw48seg.pipeline" \
                  --data_path=$PATH1 \
                  --data_lst=$PATH2 \
                  --infer_result_path="./inferResults/"

echo "SDK inference task succeeded."

