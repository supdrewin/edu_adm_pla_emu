#pragma once

#include <string>
#include <vector>

namespace zh_CN {

static std::string locale("zh_CN");

static const std::vector<std::string> menu_main{
    "添加一个学生", "查找一个学生", "添加一个考试科目", "删除一个考试科目",
    "对数据库排序", "显示数据库",   "同步写入数据库",   "账户设置",
    "退出登陆",     "退出程序",
};

static const std::vector<std::string> menu_sort{
    "按名字排序",
    "按学号排序",
    "按成绩排序",
    "返回上一级菜单",
};

static const std::vector<std::string> menu_find{
    "用名字查找学生",
    "用学号查找学生",
    "用成绩查找学生",
    "返回上一级菜单",
};

static const std::vector<std::string> menu_user{
    "显示我的成绩",
    "账户设置",
    "退出登陆",
    "退出程序",
};

static const std::vector<std::string> settings{
    "修改密码",
    "返回上一级菜单",
};

static const std::vector<std::string> manage_user{
    "显示用户信息",
    "更改用户信息",
    "删除此用户",
    "返回上一级菜单",
};

} // namespace zh_CN
