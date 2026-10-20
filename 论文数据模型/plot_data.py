import pandas as pd
import matplotlib.pyplot as plt
import os  # 【新增】导入操作系统接口库，用于自动获取绝对路径

# 解决图表中中文显示为方块的问题
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

print("正在读取数据并画图...")

try:
    # 【核心修改】动态获取当前脚本(plot_data.py)所在的绝对路径
    current_dir = os.path.dirname(os.path.abspath(__file__))
    # 拼接出数据文件的绝对路径：当前目录的上一级 -> 数据 -> 清洗结果 -> Excel文件
    file_path = os.path.join(current_dir, '../数据/清洗结果/08_最终完美面板数据.xlsx')
    
    # 使用拼接好的绝对路径读取数据
    df = pd.read_excel(file_path)
    
    df['产业结构升级指数'] = df['第三产业'] / df['第二产业']
    
    # ================= 画图 1 =================
    plt.figure(figsize=(10, 6))
    for city in df['城市'].unique():
        city_data = df[df['城市'] == city]
        plt.plot(city_data['年份'], city_data['产业结构升级指数'], marker='o', label=city)
    plt.legend()
    plt.title('大湾区9市产业结构升级指数趋势 (2020-2024)')
    plt.xlabel('年份')
    plt.ylabel('第三/第二产业比值')
    plt.grid(True)
    plt.savefig('图1_9市比值趋势.png', dpi=300, bbox_inches='tight')
    plt.close()

    # ================= 画图 2 =================
    plt.figure(figsize=(10, 6))
    for city in df['城市'].unique():
        city_data = df[df['城市'] == city]
        plt.plot(city_data['年份'], city_data['第二产业'], marker='o', label=city)
    plt.legend()
    plt.title('大湾区9市第二产业绝对值趋势 (2020-2024)')
    plt.xlabel('年份')
    plt.ylabel('第二产业增加值 (亿元)')
    plt.grid(True)
    plt.savefig('图2_二产绝对值趋势.png', dpi=300, bbox_inches='tight')
    plt.close()
    
    print("✅ 搞定！两张图已生成在当前代码文件夹下。")

except Exception as e:
    print(f"❌ 报错啦！请检查数据文件是否存在。具体错误: {e}")