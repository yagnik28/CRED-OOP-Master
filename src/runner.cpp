#include <iostream>
#include "service/FileSystemManagerImpl.hpp"

int main()
{
  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("nonExistentFolder", "file1.txt", false);
  // std::vector<std::string> contents = fileSystemManager.listContents("root");
  
  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("folder1", "subfolder1", true);
  // std::vector<std::string> contents = fileSystemManager.listContents("folder1");
  
  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "file1.txt", false);
  // fileSystemManager.moveFileOrFolder("file1.txt", "nonExistentFolder");
  // std::vector<std::string> contents = fileSystemManager.listContents("root");
  
  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("nonExistentFolder", "file1.txt", false);
  // std::vector<std::string> contents = fileSystemManager.listContents("root");

  // for(const auto &item : contents) {
  //   std::cout << item << std::endl;
  // }

  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("folder1", "folder2", true);
  // fileSystemManager.moveFileOrFolder("folder2", "root");
  // std::vector<std::string> rootContents = fileSystemManager.listContents("root");
  // std::vector<std::string> folder1Contents = fileSystemManager.listContents("folder1");

  // std::cout << "rootContents: "; 
  // for(const auto &item : rootContents) {
  //   std::cout << item << ", ";
  // }
  // std::cout << std::endl;
  // std::cout << "folder1Contents: "; 
  // for(const auto &item : folder1Contents) {
  //   std::cout << item << ", ";
  // }
  // std::cout << std::endl;

  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("folder1", "file1.txt", false);
  // std::string result = fileSystemManager.searchFileExactMatch("folder1", "file1.txt");
  // std::cout << result << std::endl;
  
  // FileSystemManagerImpl fileSystemManager("root");
  // fileSystemManager.addFileOrFolder("root", "folder1", true);
  // fileSystemManager.addFileOrFolder("folder1", "file1.txt", false);
  // fileSystemManager.addFileOrFolder("folder1", "file2.jpg", false);
  // fileSystemManager.addFileOrFolder("folder1", "subfolder", true);
  // fileSystemManager.addFileOrFolder("subfolder", "file3.txt", false);

  // std::vector<std::string> searchResults = fileSystemManager.searchFileLikeMatch("root", ".txt");

  // for(const auto &item : searchResults) {
  //   std::cout << item << std::endl;
  // }

  FileSystemManagerImpl fileSystemManager("root");
  fileSystemManager.addFileOrFolder("root", "folder1", true);
  fileSystemManager.addFileOrFolder("folder1", "file1.txt", false);
  std::vector<std::string> structure = fileSystemManager.listDirectoryStructure();
  for(const auto &item : structure) {
    std::cout << item << std::endl;
  }

  return 0;
}
