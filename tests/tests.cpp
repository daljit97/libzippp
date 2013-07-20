
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "libzippp.h"

using namespace std;
using namespace libzippp;

void test1() {
    cout << "Running test 1...";
    
    ZipFile z1("test.zip");
    assert(!z1.isOpen());
    assert(!z1.isMutable());
    z1.open(ZipFile::WRITE);
    assert(z1.isOpen());
    assert(z1.isMutable());
    bool result = z1.addDirectory("folder/subfolder/finalfolder/");
    assert(result);
    z1.close();
    assert(!z1.isOpen());
    assert(!z1.isMutable());
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::READ_ONLY);
    assert(z2.isOpen());
    assert(!z2.isMutable());
    int nbEntries = z2.getNbEntries();
    assert(nbEntries==3);
    assert(z2.hasEntry("folder/"));
    assert(z2.hasEntry("folder/subfolder/"));
    assert(z2.hasEntry("folder/subfolder/finalfolder/"));
    z2.close();
    assert(z2.unlink());
    
    cout << " done." << endl;
}

void test2() {
    cout << "Running test 2...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::READ_ONLY);
    assert(z2.getNbEntries()==1);
    assert(z2.hasEntry("somedata"));
    
    ZipEntry entry = z2.getEntry("somedata");
    assert(!entry.isNull());
    
    char* data = (char*)z2.readEntry(entry);
    int clen = strlen(data);
    assert(clen==len);
    assert(strncmp(txtFile, data, len)==0);
    
    z2.close();
    z2.unlink();
    
    cout << " done." << endl;
}

void test3() {
    cout << "Running test 3...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolder/data.txt", txtFile, len);
    assert(z1.addDirectory("somedata/"));
    assert(z1.addDirectory("in/"));
    assert(z1.addDirectory("in/subfolder/"));
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::READ_ONLY);
    assert(z2.getNbEntries()==6);
    assert(z2.hasEntry("somedata/in/subfolder/data.txt"));
    
    ZipEntry entry = z2.getEntry("somedata/in/subfolder/data.txt");
    assert(!entry.isNull());
    
    char* data = (char*)z2.readEntry(entry);
    int clen = strlen(data);
    assert(clen==len);
    assert(strncmp(txtFile, data, len)==0);
    
    z2.close();
    z2.unlink();
    
    cout << " done." << endl;
}

void test4() {
    cout << "Running test 4...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==2);
    
    ZipEntry d = z2.getEntry("somedata/test.txt");
    assert(!d.isNull() && d.isFile());
    assert(z2.deleteEntry(d)==1);
    z2.close();
    z2.unlink();
    
    cout << " done." << endl;
}

void test5() {
    cout << "Running test 5...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==4);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.deleteEntry(d)==3);
    z2.close();
    z2.unlink();
    
    cout << " done." << endl;
}

void test6() {
    cout << "Running test 6...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==4);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.renameEntry(d, "somedata/out/")==3);
    z2.close();
    z2.unlink();
    
    cout << " done." << endl;
}

void test7() {
    cout << "Running test 7...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==4);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.renameEntry(d, "somedata/in/subfolder/")==3);
    z2.close();
    
    ZipFile z3("test.zip");
    z3.open(ZipFile::READ_ONLY);
    assert(z3.getNbEntries()==5);
    z3.close();
    z3.unlink();
    
    cout << " done." << endl;
}

void test8() {
    cout << "Running test 8...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==4);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.renameEntry(d, "newdata/out/subfolders/")==3);
    z2.close();
    
    ZipFile z3("test.zip");
    z3.open(ZipFile::READ_ONLY);
    assert(z3.getNbEntries()==6);
    z3.close();
    z3.unlink();
    
    cout << " done." << endl;
}

void test9() {
    cout << "Running test 9...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.addData("somedata/out/subfolders/other.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==7);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.renameEntry(d, "root/")==3);
    z2.close();
    
    ZipFile z3("test.zip");
    z3.open(ZipFile::READ_ONLY);
    assert(z3.getNbEntries()==7);
    z3.close();
    z3.unlink();
    
    cout << " done." << endl;
}

void test10() {
    cout << "Running test 10...";
    
    const char* txtFile = "this is some data";
    int len = strlen(txtFile);
    
    ZipFile z1("test.zip");
    z1.open(ZipFile::WRITE);
    z1.addData("somedata/in/subfolders/test.txt", txtFile, len);
    z1.close();
    
    ZipFile z2("test.zip");
    z2.open(ZipFile::WRITE);
    assert(z2.getNbEntries()==4);
    
    ZipEntry d = z2.getEntry("somedata/in/");
    assert(!d.isNull() && d.isDirectory());
    assert(z2.renameEntry(d, "newdata/out/subfolders/")==3);
    z2.discard();
    
    ZipFile z3("test.zip");
    z3.open(ZipFile::READ_ONLY);
    assert(z3.getNbEntries()==4);
    z3.close();
    z3.unlink();
    
    cout << " done." << endl;
}

int main(int argc, char** argv) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}

