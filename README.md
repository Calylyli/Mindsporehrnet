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
* 准备数据集  ([**cityscapes**](https://paperswithcode.com/dataset/cityscapes)).
```
├─ cityscapes                           # cityscapes数据集根目录
│   ├─ gtFine                           # 标签文件
│   │   ├─ train                        # 训练标签文件
│   │   │   └─ [city folders]
│   │   │       └─ [label images]
│   │   └─ val                          # 推理标签文件
│   │       └─ [city folders]
│   │           └─ [label images]
│   ├─ leftImg8bit                      # 图像文件
│   │   ├─ train                        # 训练图像文件
│   │   │   └─ [city folders]
│   │   │       └─ [images]
│   │   └─ val                          # 推理图像文件
│   │       └─ [city folders]
│   │           └─ [images]
│   ├─ train.lst                        # 训练样本列表
│   └─ val.lst                          # 推理样本列表
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

### 3. 评估
* 运行如下代码 : 
```bash
sh scripts/run_eval.sh [DEVICE_ID] [DATASET_PATH] [CHECKPOINT_PATH]
```

### 4. 推理
* 运行如下代码 : 
```bash
sh scripts/ascend310_inference.sh [MINDIR_PATH] [DATA_PATH] [DEVICE_ID]
```


## References
* **Link**: [Show and tell: A neural image caption generator](https://arxiv.org/abs/1411.4555)
* **Link**: https://github.com/nalbert9/Image-Captioning
