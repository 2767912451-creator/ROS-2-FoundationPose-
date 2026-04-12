#!/usr/bin/env python3
"""
使用 trimesh 实现高质量 STL 转 OBJ。
自动合并重复顶点、修复法线方向并移除无用数据，生成高质量的OBJ模型。
"""

import trimesh
import sys
from pathlib import Path

def convert_stl_to_obj(input_path, output_path=None):
    """
    将 STL 文件高质量地转换为 OBJ 文件。
    
    Args:
        input_path (str): 输入的 .stl 文件路径。
        output_path (str, optional): 输出的 .obj 文件路径。
                                    若未指定，则自动在输入文件同目录下生成。
    """
    input_file = Path(input_path)
    
    # 1. 检查输入文件是否存在
    if not input_file.is_file():
        raise FileNotFoundError(f"找不到指定的 STL 文件: {input_path}")
    
    # 2. 自动确定输出路径
    if output_path is None:
        output_file = input_file.with_suffix('.obj')
    else:
        output_file = Path(output_path)
    
    # 3. 使用 trimesh 加载并自动修复网格
    print(f"正在加载并修复网格: {input_file.name}")
    mesh = trimesh.load_mesh(input_file)
    
    # 4. 核心修复步骤：验证网格，合并重复顶点，移除孤立顶点，确保法线一致
    print("正在执行网格优化：合并重复顶点、修复法线方向...")
    mesh.process(validate=True)
    mesh.remove_unreferenced_vertices()
    
    # 5. 导出为高质量的 OBJ 文件
    print(f"正在导出至: {output_file.name}")
    mesh.export(output_file)
    
    print("转换完成！")

if __name__ == "__main__":
    # 获取命令行参数
    if len(sys.argv) < 2:
        print("用法: python stl2obj.py <输入的.stl文件> [输出的.obj文件]")
        sys.exit(1)
    
    # 执行转换
    input_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else None
    convert_stl_to_obj(input_path, output_path)