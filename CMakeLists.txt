cmake_minimum_required(VERSION 3.8)
project(Algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        TP1/CardGameWar/Card.cpp
        TP1/CardGameWar/Card.h
        TP1/CardGameWar/Game.cpp
        TP1/CardGameWar/Game.h
        TP1/CardGameWar/Player.cpp
        TP1/CardGameWar/Player.h
        TP1/CardGameWar/Stack.h
        TP1/Dictionnary/Dictionnary.cpp
        TP1/Dictionnary/Dictionnary.h
        TP1/Dictionnary/stdafx.cpp
        TP1/Dictionnary/stdafx.h
        TP1/Dictionnary/targetver.h
        TP1/Factory/Factory.cpp
        TP1/Factory/File.cpp
        TP1/Factory/File.h
        TP1/Factory/stdafx.cpp
        TP1/Factory/stdafx.h
        TP1/Factory/targetver.h
        TP1/GenealogyTree/FamilyTree.cpp
        TP1/GenealogyTree/FamilyTree.h
        TP1/GenealogyTree/main.cpp
        TP1/GenealogyTree/NTree.cpp
        TP1/GenealogyTree/NTree.h
        TP1/GenealogyTree/Person.cpp
        TP1/GenealogyTree/Person.h
        TP1/GenealogyTree/stdafx.cpp
        TP1/GenealogyTree/stdafx.h
        TP1/GenealogyTree/targetver.h
        TP1/GenealogyTree/TreeNode.cpp
        TP1/GenealogyTree/TreeNode.h)

add_executable(Algorithms ${SOURCE_FILES})