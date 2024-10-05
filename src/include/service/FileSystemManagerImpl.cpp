#include "FileSystemManagerImpl.hpp"
#include "models/Folder.hpp"
#include "models/FileSystemItem.hpp"
#include "models/File.hpp"
#include <iostream>
#include <map>

std::map<std::string, FileSystemItem*> object;
std::map<FileSystemItem*, Folder*> parent;

FileSystemManagerImpl::FileSystemManagerImpl(const std::string &rootName) : root(rootName) {
    object[rootName] = &root;
}

void
FileSystemManagerImpl::addFileOrFolder(const std::string &parentFolderName, const std::string &name, bool isFolder) {
    bool found = false;
    Folder *parentFolder = (Folder*)object[parentFolderName];
    if(parentFolder == nullptr) {
        return;
    }
    FileSystemItem *itemToAdd;
    if(isFolder) {
        itemToAdd = new Folder(name);
    }
    else {
        itemToAdd = new File(name);
    }
    parentFolder -> addItem(itemToAdd);
    object[name] = itemToAdd;
    parent[itemToAdd] = parentFolder;
}

void FileSystemManagerImpl::moveFileOrFolder(const std::string &sourceName, const std::string &destinationFolderName) {
    FileSystemItem *srcItem = object[sourceName];
    if(srcItem == nullptr) {
        return;
    }
    FileSystemItem *destItem = object[destinationFolderName];
    if(destItem == nullptr) {
        return;
    }
    Folder *destItemFolder = (Folder*)destItem;
    Folder *copiedSourceFolder = new Folder(sourceName);
    destItemFolder -> addItem(copiedSourceFolder);
    object.erase(sourceName);
    parent[srcItem] -> removeItem(srcItem);
}

std::vector<std::string> FileSystemManagerImpl::listContents(const std::string &folderName) const {
    FileSystemItem *folderItem = object[folderName];
    if(folderItem == nullptr) {
        return {};
    }
    Folder *folder = (Folder*)folderItem;
    std::vector<std::string> folderContent;
    for(const auto &item : folder -> getItems()) {
        folderContent.push_back(item -> getName());
    }
    return folderContent;
}

void traverse(const Folder *curFolder, int level, std::vector<std::string> &content) {
    for(const auto &item : curFolder -> getItems()) {
        if(item -> isFolder()) {
            std::string curFolder = std::string(level, ' ') + "+ " + item -> getName();
            content.push_back(curFolder);
            Folder *Item = (Folder*)item;
            traverse(Item, level + 2, content);
        }
        else {
            std::string curFile = std::string(level, ' ') + "- " + item -> getName();
            content.push_back(curFile);
        }
    }
}

std::vector<std::string> FileSystemManagerImpl::listDirectoryStructure() const {
    std::vector<std::string> content;
    std::string rootFolder = "+ " + root.getName();
    content.push_back(rootFolder);
    traverse(&root, 2, content);
    return content;
}


std::string
FileSystemManagerImpl::searchFileExactMatch(const std::string &folderName, const std::string &fileName) const {
    FileSystemItem *folderItem = object[folderName];
    if(folderItem == nullptr) {
        return "";
    }
    Folder *folder = (Folder*)folderItem;
    for(const auto &item : folder -> getItems()) {
        if(item -> isFolder()) {
            continue;
        }
        if(item -> getName() == fileName) {
            return fileName;
        }
    }
    return "";
}

bool compare(const std::string original, const std::string pattern) {
    int n = original.size(), m = pattern.size();
    for(int i = 0; i < n - m + 1; i++) {
        if(original.substr(i, m) == pattern) {
            return true;
        }
    }
    return false;
}

std::string convert(const std::string &original) {
    std::string lowerCaseOriginal = "";
    for(const auto &ch : original) {
        if('A' <= ch && ch <= 'Z') lowerCaseOriginal += char(ch - 'A' + 'a');
        else lowerCaseOriginal += ch;
    }
    return lowerCaseOriginal;
}

void matchFile(const Folder *curFolder, const std::string &pattern, std::vector<std::string> &content) {
    for(const auto &item : curFolder -> getItems()) {
        if(item -> isFolder()) {
            Folder *Item = (Folder*)item;
            matchFile(Item, pattern, content);
            continue;
        }
        if(compare(convert(item -> getName()), pattern)) {
            content.push_back(item -> getName());
        }
    }
}

std::vector<std::string>
FileSystemManagerImpl::searchFileLikeMatch(const std::string &folderName, const std::string &pattern) const {
    FileSystemItem *folderItem = object[folderName];
    if(folderItem == nullptr) {
        return {};
    }
    std::vector<std::string> content;
    Folder *folder = (Folder*)folderItem;
    std::string lowerCasePattern = convert(pattern);
    matchFile(folder, lowerCasePattern, content);
    return content;
}