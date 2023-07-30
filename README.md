# 
<h1 align="center">
        Show&Tell
</h1>
<h4 align="center">
    <p>
        <b>简体中文</b> 
    </p>
</h4>

<h3 align="center">
    <p>基于Mindspore实现“Deep High-Resolution Representation Learning for Visual Recognition"</p>
</h3>



## 必要前提

* Mindspore=2.0.0
* HRNet

## 使用方法
克隆该仓库:
```bash
git clone https://github.com/Calylyli/Mindsporehrnet.git
```

### 1. Flickr8k Dataset 
* 准备数据集  ([**Flickr8k**](https://www.kaggle.com/shadabhussain/flickr8k)). 
* 提取图片到**Images**文件夹，提取文本到**captions.txt**文件. 
* 把**Images**and**captions.txt** 放到同一个文件夹（**flickr8k**）下 
```angular2html
-- flickr8k
    |-- Images
      |-- 1000268201_693b08cb0e.jpg
      |-- ......
    |-- captions.txt
```


### 2. 训练
* 运行如下代码 : 
```bash
python train.py
```


### 2. 导出MindIR
* 运行如下代码 : 
```bash
python export.py --device_id [DEVICE_ID] --checkpoint_file [CKPT_PATH] --file_name [FILE_NAME] --file_format MINDIR --device_target Ascend --dataset [DATASET]
```

### 3. 推理
* 运行如下代码 : 
```bash
sh scripts/ascend310_inference.sh [MINDIR_PATH] [DATA_PATH] [DEVICE_ID]
```


## References
* **Link**: [Show and tell: A neural image caption generator](https://arxiv.org/abs/1411.4555)
* **Link**: https://github.com/nalbert9/Image-Captioning