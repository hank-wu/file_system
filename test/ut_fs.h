#ifndef UT_FS_H
#define UT_FS_H

#include <memory>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/node.h"
#include "../src/link.h"
#include "../src/info_content_visitor.h"
#include "../src/node_iterator.h"
#include "../src/find_visitor.h"
#include "../src/node_builder.h"
#include "../src/find_link_visitor.h"
#include "../src/find_node_by_pathname_visitor.h"


TEST (MiscTest, lstatOnFolder)
{
  const char * path = "./test_data";
  struct stat st;
  ASSERT_EQ(0, lstat(path, &st));
  ASSERT_EQ(4096, st.st_size);
  ASSERT_EQ(true, S_ISDIR(st.st_mode));
  ASSERT_EQ(false, S_ISREG(st.st_mode));
  ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

class FileSystemTest: public ::testing::Test
{
protected:
  void SetUp() override
  {
    test_data = new Folder ("test_data");
    folder = new Folder("./test_data/folder");
    hello_cpp = new File("./test_data/hello.cpp");
    a_out = new File("./test_data/folder/a.out");
    hello = new Link("./test_data/hello", a_out);
    folder->add(a_out);
    test_data->add(folder);
    test_data->add(hello);
    test_data->add(hello_cpp);
  }

  void TearDown() override
  {
    delete a_out;
    delete hello_cpp;
    delete hello;
    delete folder;
    delete test_data;
  }

  Node * test_data;
  Node * folder;
  Node * hello_cpp;
  Node * a_out;
  Node * hello;

};

TEST_F (FileSystemTest, NodeBuilderOnFile) {
  NodeBuilder nb;
  nb.build("test_data/hello.cpp");
  ASSERT_EQ(89, nb.getRoot()->size());

  nb.build("test_data/hello");
  ASSERT_EQ(12, nb.getRoot()->size());
  // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());

  nb.build("./test_data/folder/a.out");
  ASSERT_EQ(8432, nb.getRoot()->size());

  nb.build("test_data/folder");
  ASSERT_EQ(4096, nb.getRoot()->size());  

  std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
  it->first();
  // // ASSERT_TRUE(it->isDone());
  ASSERT_EQ(8432, it->currentItem()->size());
 
  it->next();
  ASSERT_TRUE(it->isDone());

  nb.build("test_data");
  ASSERT_EQ(4096, nb.getRoot()->size());
  std::unique_ptr<NodeIterator> it1(nb.getRoot()->createIterator());
  it1->first();
  ASSERT_EQ(4096, it1->currentItem()->size());
  it1->next();
  ASSERT_EQ(12, it1->currentItem()->size());
  it1->next();
  ASSERT_EQ(89, it1->currentItem()->size());
  it1->next();
  ASSERT_TRUE(it1->isDone());
}

TEST_F (FileSystemTest, Visitor)
{
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(8432, icv->getContentSize());
  delete icv;

  InfoContentVisitor * icv10 = new InfoContentVisitor();
  hello->accept(icv10);
  ASSERT_EQ(8432,icv10->getContentSize());
  // icv = new InfoContentVisitor("");
  InfoContentVisitor * icv2 = new InfoContentVisitor();
  folder->accept(icv2);
  ASSERT_EQ(8432, icv2->getContentSize());

  InfoContentVisitor * icv3 = new InfoContentVisitor();
  test_data->accept(icv3);
  ASSERT_EQ(16953,icv3->getContentSize());
}

TEST_F (FileSystemTest, FindLinkVisitor) {
  NodeBuilder nb;
  nb.build("test_data");
  Node * test_data1 = nb.getRoot();
  FindLinkVisitor * flv = new FindLinkVisitor;
  test_data1->accept(flv);
  ASSERT_EQ(1,flv->getLinks().size());
  std::vector<Node*>temp = flv->getLinks();
  ASSERT_EQ(1, temp.size());
  std::vector<Node*>::iterator it = temp.begin();
  ASSERT_EQ(12, (*it)->size());
}

TEST(NodeBuilder, file){
  NodeBuilder nb;
  nb.build("makefile");
  ASSERT_EQ(1843, nb.getRoot()->size());
}

TEST_F (FileSystemTest, NodeTypeError)
{
  ASSERT_ANY_THROW(new File("./test_data/folder"));//Do not indicate the file path.
  ASSERT_ANY_THROW(new Folder("./test_data/hello"));//Do not indicate the Folder path.
  ASSERT_ANY_THROW(new Link("./test_data/hello.cpp"));//Do not indicate the Link path.
}

TEST (FindNodeByPathnameVisitor, Link){
  Node * hello = new Link("./test_data/hello");
  std::vector<std::string>* names = new std::vector<std::string>{std::string("hello")};
  FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
  hello->accept(fv);
  ASSERT_EQ(hello, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, File){
  Node * hello = new File("./test_data/hello.cpp");
  std::vector<std::string>* names = new std::vector<std::string>{std::string("hello.cpp")};
  FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
  hello->accept(fv);
  ASSERT_EQ(hello, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, FolderOneLevel){
  Node * testData = new Folder("./test_data");
  std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data")};
  FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
  testData->accept(fv);
  ASSERT_EQ(testData, fv->getNode());
}
TEST (FindNodeByPathnameVisitor, LinkInFolder){
  Node * test_data = new Folder ("./test_data");
  Node * hello = new Link("./test_data/hello");
  test_data->add(hello);
  std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("hello")};
  FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
  test_data->accept(fv);
  ASSERT_EQ(hello, fv->getNode());
}
TEST (FindNodeByPathnameVisitor, nonExistingFileInFileSystem){
  Node * test_data = new Folder ("./test_data");
  std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("helloWorld")};
  FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
  test_data->accept(fv);
  ASSERT_EQ(nullptr, fv->getNode());
}


TEST (biuldTest,parent){
  Node * test_data = new Folder ("test_data");
  Node * hello = new Link("./test_data/hello");
  test_data->add(hello);
  ASSERT_EQ(std::string("test_data"), hello->getParent()->name());
}

TEST(folderTest, folder){
  Folder * test_data = new Folder ("./test_data");
  Node * hello = new Link("./test_data/hello");
  test_data->add(hello);
}

#endif
