cmake_minimum_required(VERSION 3.8)
project(TP1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CardGameWar/Card.cpp
        CardGameWar/Card.h
        CardGameWar/Game.cpp
        CardGameWar/Game.h
        CardGameWar/Player.cpp
        CardGameWar/Player.h
        CardGameWar/Stack.h
        Dictionnary/Dictionnary.cpp
        Dictionnary/Dictionnary.h
        Dictionnary/stdafx.cpp
        Dictionnary/stdafx.h
        Dictionnary/targetver.h
        Factory/Factory.cpp
        Factory/File.cpp
        Factory/File.h
        Factory/stdafx.cpp
        Factory/stdafx.h
        Factory/targetver.h
        GenealogyTree/main.cpp
        GenealogyTree/Person.cpp
        GenealogyTree/Person.h
        GenealogyTree/stdafx.cpp
        GenealogyTree/stdafx.h
        GenealogyTree/targetver.h
        GenealogyTree/TreeNode.cpp
        GenealogyTree/TreeNode.h GenealogyTree/NTree.cpp GenealogyTree/NTree.h GenealogyTree/FamilyTree.cpp GenealogyTree/FamilyTree.h)

add_executable(TP1 ${SOURCE_FILES})