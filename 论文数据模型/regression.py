# 导入数据处理核心库 pandas，并简写为 pd
import pandas as pd

# 从 linearmodels 库中导入 PanelOLS，这是专门用来跑面板数据回归的模型
from linearmodels.panel import PanelOLS

# 导入数学运算库 numpy，简写为 np，主要用于计算自然对数
import numpy as np

# 导入操作系统接口库 os，用于动态获取文件的绝对路径，防止在不同电脑上找不到文件
import os

# 在终端打印一行提示，让你知道程序开始运行了
print("开始跑计量回归分析...")

# 使用 try-except 异常处理结构，如果代码报错，程序不会直接崩溃，而是会打印出错误原因
try:
    # 【路径防呆设计】获取当前运行的 regression.py 脚本所在的绝对文件夹路径
    current_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 使用 os.path.join 拼接出数据文件的绝对路径：当前目录的上一级 -> 数据 -> 清洗结果 -> Excel文件
    file_path = os.path.join(current_dir, '../数据/清洗结果/08_最终完美面板数据.xlsx')
    
    # 读取拼接好路径的 Excel 面板数据，并赋值给变量 df
    df = pd.read_excel(file_path)
    
    # ================= 1. 核心变量构造 =================
    # 构造论文的核心因变量：三产/二产比值。用 DataFrame 的列相除即可
    df['Y_比值'] = df['第三产业'] / df['第二产业'] 
    
    # 构造稳健性检验用的替换因变量：第三产业增加值占GDP比重
    df['Y_三产占比'] = df['第三产业'] / df['GDP']
    
    # 对核心自变量常住人口取自然对数。加上 1e-5 是极其严谨的写法，防止个别数据为0导致 log(0) 报错
    df['ln_人口'] = np.log(df['常住人口'] + 1e-5)
    
    # 对控制变量 GDP 取自然对数
    df['ln_GDP'] = np.log(df['GDP'] + 1e-5)

    # 设定核心城市名单（根据论文设定：广州、深圳、佛山、东莞为核心城市）
    core_cities = ['广州', '深圳', '佛山', '东莞']
    
    # 构造虚拟变量：使用 apply 和 lambda 函数遍历城市列，如果在名单里赋值为1，否则为0
    df['是否核心'] = df['城市'].apply(lambda x: 1 if x in core_cities else 0)

    # 构造交互项：核心解释变量（人口对数） 乘以 虚拟变量（是否核心城市），这是异质性分析的关键
    df['交互项'] = df['ln_人口'] * df['是否核心']

    # 剔除数据集中可能存在的空值（NaN），只保留计算所需的列，防止回归报错
    df = df.dropna(subset=['Y_比值', 'Y_三产占比', 'ln_人口', 'ln_GDP', '交互项'])
    
    # 极其关键的一步：设置双重索引。告诉模型，数据的第一层是城市（个体），第二层是年份（时间）
    df = df.set_index(['城市', '年份'])

    # ================= 模型 1：基准回归 =================
    # 设定公式：Y_比值 对 ln_人口 和 ln_GDP 回归。EntityEffects 代表城市固定效应，TimeEffects 代表年份固定效应
    formula_1 = 'Y_比值 ~ 1 + ln_人口 + ln_GDP + EntityEffects + TimeEffects'
    
    # 拟合模型。cov_type='clustered' 表示使用聚类稳健标准误，cluster_entity=True 表示聚类到城市级别
    res1 = PanelOLS.from_formula(formula_1, data=df).fit(cov_type='clustered', cluster_entity=True)
    
    # 打印模型结果中的系数表（即论文中的表1第一列）
    print("\n=== 表1 (1) 基准回归结果 ===")
    print(res1.summary.tables[1])

    # ================= 模型 2：交互项异质性分析 =================
    # 设定公式：在模型1的基础上，加入"交互项"，用于识别核心城市与边缘城市的差异
    formula_2 = 'Y_比值 ~ 1 + ln_人口 + 交互项 + ln_GDP + EntityEffects + TimeEffects'
    
    # 同样使用聚类稳健标准误进行拟合
    res2 = PanelOLS.from_formula(formula_2, data=df).fit(cov_type='clustered', cluster_entity=True)
    
    # 打印结果（即论文中的表1第二列，验证核心城市的正向集聚与边缘城市的负向流失）
    print("\n=== 表1 (2) 交互项异质性结果 ===")
    print(res2.summary.tables[1])

    # ================= 模型 3：稳健性检验 =================
    # 设定公式：将因变量替换为 Y_三产占比，其他变量保持不变，用于证明结论的稳健性
    formula_3 = 'Y_三产占比 ~ 1 + ln_人口 + 交互项 + ln_GDP + EntityEffects + TimeEffects'
    
    # 拟合模型
    res3 = PanelOLS.from_formula(formula_3, data=df).fit(cov_type='clustered', cluster_entity=True)
    
    # 打印结果（即论文中的表2，验证核心规律是否依然显著）
    print("\n=== 表2 稳健性检验结果 ===")
    print(res3.summary.tables[1])

# 如果 try 里面的代码发生了任何报错，会跳转到这里执行
except Exception as e:
    # 打印出具体的报错信息，方便我们定位问题
    print(f"❌ 报错啦！具体错误: {e}")