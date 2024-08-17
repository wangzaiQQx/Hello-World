import os
import shutil

def move_files_and_remove_empty_folders(source_folder, destination_folder):
    # 遍历源文件夹
    for root, dirs, files in os.walk(source_folder, topdown=False):
        for name in files:
            # 源文件路径
            source_file = os.path.join(root, name)
            # 目标文件路径
            destination_file = os.path.join(destination_folder, name)
            # 移动文件
            shutil.move(source_file, destination_file)
        for name in dirs:
            # 移除空文件夹
            folder = os.path.join(root, name)
            if not os.listdir(folder):
                os.rmdir(folder)

# 设置源文件夹和目标文件夹路径
source_folder = './'
destination_folder = './'

# 移动文件并删除空文件夹
move_files_and_remove_empty_folders(source_folder, destination_folder)
