/*--------------------------------------------------------------------------------------------------
 *                       Copyright (c) Ayyoub EL Kouri. All rights reserved
 *     Becoming an expert won't happen overnight, but with a bit of patience, you'll get there
 *------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include "RedBlackTree.hh"
#include "../Utils/performance.hh"

int main() {
   RedBlackTree<std::string> tree;
   std::string word;


   // Open big files
   std::string path = "../Utils/big_files_for_benchmarking/";

   std::ifstream file1(path + "1M_words.txt");
   std::ifstream file2(path + "2M_words.txt");
   std::ifstream file3(path + "3M_words.txt");
   std::ifstream file4(path + "4M_words.txt");
   std::ifstream file5(path + "5M_words.txt");
   std::ifstream file6(path + "6M_words.txt");
   std::ifstream file7(path + "7M_words.txt");
   std::ifstream file8(path + "8M_words.txt");
   std::ifstream file9(path + "9M_words.txt");
   std::ifstream file10(path + "10M_words.txt");

   // Check that all files opening successfuly
   if (  !file1.is_open() ||
         !file2.is_open() ||
         !file3.is_open() ||
         !file4.is_open() ||
         !file5.is_open() ||
         !file6.is_open() ||
         !file7.is_open() ||
         !file8.is_open() ||
         !file9.is_open() ||
         !file10.is_open()
      ) {
      std::cerr << "Error opening one or more files." << std::endl;
      return 1;
   }

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 1 million words ======================================

   // Insertion -------------------------------
   Performance insertion1M("1M-Insertion");

   insertion1M.start();
   while (file1 >> word) {
      tree.insert(word);
   }
   insertion1M.stop();

   insertion1M.print();


   // Search ----------------------------------
   Performance search1M("1M-Search");

   search1M.start();
   tree.contains("Ayyoub");
   search1M.stop();

   search1M.print();


   // Remove ----------------------------------
   Performance remove1M("1M-Remove");

   remove1M.start();
   tree.remove("ayyoub");
   remove1M.stop();

   remove1M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

      // ======================================= 2 million words ======================================

   // Insertion -------------------------------
   Performance insertion2M("2M-Insertion");

   insertion2M.start();
   while (file2 >> word) {
      tree.insert(word);
   }
   insertion2M.stop();

   insertion2M.print();


   // Search ----------------------------------
   Performance search2M("2M-Search");

   search2M.start();
   tree.contains("Ayyoub");
   search2M.stop();

   search2M.print();


   // Remove ----------------------------------
   Performance remove2M("2M-Remove");

   remove2M.start();
   tree.remove("ayyoub");
   remove2M.stop();

   remove2M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 3 million words ======================================

   // Insertion -------------------------------
   Performance insertion3M("3M-Insertion");

   insertion3M.start();
   while (file3 >> word) {
      tree.insert(word);
   }
   insertion3M.stop();

   insertion3M.print();


   // Search ----------------------------------
   Performance search3M("3M-Search");

   search3M.start();
   tree.contains("Ayyoub");
   search3M.stop();

   search3M.print();


   // Remove ----------------------------------
   Performance remove3M("3M-Remove");

   remove3M.start();
   tree.remove("ayyoub");
   remove3M.stop();

   remove3M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 4 million words ======================================

   // Insertion -------------------------------
   Performance insertion4M("4M-Insertion");

   insertion4M.start();
   while (file4 >> word) {
      tree.insert(word);
   }
   insertion4M.stop();

   insertion4M.print();

   // Search ----------------------------------
   Performance search4M("4M-Search");

   search4M.start();
   tree.contains("Ayyoub");
   search4M.stop();

   search4M.print();


   // Remove ----------------------------------
   Performance remove4M("4M-Remove");

   remove4M.start();
   tree.remove("ayyoub");
   remove4M.stop();

   remove4M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 5 million words ======================================

   // Insertion -------------------------------
   Performance insertion5M("5M-Insertion");

   insertion5M.start();
   while (file5 >> word) {
      tree.insert(word);
   }
   insertion5M.stop();

   insertion5M.print();


   // Search ----------------------------------
   Performance search5M("5M-Search");

   search5M.start();
   tree.contains("Ayyoub");
   search5M.stop();

   search5M.print();


   // Remove ----------------------------------
   Performance remove5M("5M-Remove");

   remove5M.start();
   tree.remove("ayyoub");
   remove5M.stop();

   remove5M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 6 million words ======================================

   // Insertion -------------------------------
   Performance insertion6M("6M-Insertion");

   insertion6M.start();
   while (file6 >> word) {
      tree.insert(word);
   }
   insertion6M.stop();

   insertion6M.print();


   // Search ----------------------------------
   Performance search6M("6M-Search");

   search6M.start();
   tree.contains("Ayyoub");
   search6M.stop();

   search6M.print();


   // Remove ----------------------------------
   Performance remove6M("6M-Remove");

   remove6M.start();
   tree.remove("ayyoub");
   remove6M.stop();

   remove6M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 7 million words ======================================

   // Insertion -------------------------------
   Performance insertion7M("7M-Insertion");

   insertion7M.start();
   while (file7 >> word) {
      tree.insert(word);
   }
   insertion7M.stop();

   insertion7M.print();


   // Search ----------------------------------
   Performance search7M("7M-Search");

   search7M.start();
   tree.contains("Ayyoub");
   search7M.stop();

   search7M.print();


   // Remove ----------------------------------
   Performance remove7M("7M-Remove");

   remove7M.start();
   tree.remove("ayyoub");
   remove7M.stop();

   remove7M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 8 million words ======================================

   // Insertion -------------------------------
   Performance insertion8M("8M-Insertion");

   insertion8M.start();
   while (file8 >> word) {
      tree.insert(word);
   }
   insertion8M.stop();

   insertion8M.print();


   // Search ----------------------------------
   Performance search8M("8M-Search");

   search8M.start();
   tree.contains("Ayyoub");
   search8M.stop();

   search8M.print();


   // Remove ----------------------------------
   Performance remove8M("8M-Remove");

   remove8M.start();
   tree.remove("ayyoub");
   remove8M.stop();

   remove8M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 9 million words ======================================

   // Insertion -------------------------------
   Performance insertion9M("9M-Insertion");

   insertion9M.start();
   while (file9 >> word) {
      tree.insert(word);
   }
   insertion9M.stop();

   insertion9M.print();


   // Search ----------------------------------
   Performance search9M("9M-Search");

   search9M.start();
   tree.contains("Ayyoub");
   search9M.stop();

   search9M.print();


   // Remove ----------------------------------
   Performance remove9M("9M-Remove");

   remove9M.start();
   tree.remove("ayyoub");
   remove9M.stop();

   remove9M.print();

   tree.clear();

   std::cout << "---------------------------------------" << std::endl;

   // ======================================= 10 million words ======================================

   // Insertion -------------------------------
   Performance insertion10M("10M-Insertion");

   insertion10M.start();
   while (file10 >> word) {
      tree.insert(word);
   }
   insertion10M.stop();

   insertion10M.print();


   // Search ----------------------------------
   Performance search10M("10M-Search");

   search10M.start();
   tree.contains("Ayyoub");
   search10M.stop();

   search10M.print();


   // Remove ----------------------------------
   Performance remove10M("10M-Remove");

   remove10M.start();
   tree.remove("ayyoub");
   remove10M.stop();

   remove10M.print();

   tree.clear();

   return 0;
}