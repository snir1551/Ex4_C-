/**
 * Created by Netanel Albert
 * Date: 2020-4 
 */

#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>


using namespace family;

Tree *test_tree(){ // helper function for other tests
    Tree *T  = new Tree("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	CHECK_NOTHROW(T->addFather("Yosef", "Yaakov"));   // Tells the tree that the father of Yosef is Yaakov.
	CHECK_NOTHROW(T->addMother("Yosef", "Rachel"));   // Tells the tree that the mother of Yosef is Rachel.
	CHECK_NOTHROW(T->addFather("Yaakov", "Isaac"));
	CHECK_NOTHROW(T->addMother("Yaakov", "Rivka"));
	CHECK_NOTHROW(T->addFather("Isaac", "Avraham"));
	CHECK_NOTHROW(T->addMother("Isaac", "Sara"));
	CHECK_NOTHROW(T->addFather("Avraham", "Terah"));
    
	CHECK_NOTHROW(T->addFather("Rivka", "Betuel"));
    CHECK_NOTHROW(T->addFather("Rachel", "Lavan"));
    CHECK_NOTHROW(T->addFather("Sara", "Haran"));
    CHECK_NOTHROW(T->addFather("Betuel", "Nahor"));
    CHECK_NOTHROW(T->addMother("Betuel", "Milca")); 

     return T;
}

TEST_CASE("add father") {
   Tree t("Nati");
   CHECK_NOTHROW(t.addFather("Nati", "Nadav"));
   CHECK_NOTHROW(t.addFather("Nadav", "Haim"));
   CHECK_NOTHROW(t.addFather("Haim", "Dori"));

   CHECK(t.find("father") == "Nadav");
   CHECK(t.find("grandfather") == "Haim");
   CHECK(t.find("great-grandfather") == "Dori");

   CHECK_THROWS(t.addFather("Nati", "Nadav")); // Nati alredy have a father
   CHECK_THROWS(t.addFather("Nadav", "Avi")); // Nadav alredy have a father
   CHECK_THROWS(t.addFather("Dani", "Avi")); // Dani not exist
}

TEST_CASE("add mother") {
   Tree t("Nati");
   CHECK_NOTHROW(t.addMother("Nati", "Orit"));
   CHECK_NOTHROW(t.addMother("Orit", "Aliza"));
   CHECK_NOTHROW(t.addMother("Aliza", "Chyia"));

   CHECK(t.find("mother") == "Orit");
   CHECK(t.find("grandmother") == "Aliza");
   CHECK(t.find("great-grandmother") == "Chyia");

   CHECK_THROWS(t.addMother("Nati", "Orit")); // Nati alredy have a mother
   CHECK_THROWS(t.addMother("Orit", "Ruti")); // Orit alredy have a mother
   CHECK_THROWS(t.addMother("Dani", "Ruti")); // Dani not exist

}

TEST_CASE("add father & mother chaining") {
    Tree t("Nati");
    CHECK_NOTHROW(t.addMother("Nati", "bla").addFather("Nati", "plip").addMother("bla","qwerty"));     
}

TEST_CASE("display") {
    Tree *T;
    CHECK_NOTHROW(T = test_tree());
    CHECK_NOTHROW(T->display()); 
    /*
    Need to print:
    Display Yosef tree. Father = up, mother = down.
				            /``Terah
			        /``Avraham
		    /``Isaac
				            /``Haran
			        \_Sara
	/``Yaakov
				            /``Nahor
			        /``Betuel
				            \_Milca
		    \_Rivka
Yosef
		    /``Lavan
	\_Rachel
    */

    delete T;
}

TEST_CASE("relation") {
    Tree *T;
    CHECK_NOTHROW(T = test_tree());

    CHECK(T->relation("Yosef") == "me");
    CHECK(T->relation("Yaakov") == "father");
    CHECK(T->relation("Isaac") == "grandfather");
    CHECK(T->relation("Avraham") == "great-grandfather");
    CHECK(T->relation("Terah") == "great-great-grandfather");
    CHECK(T->relation("Sara") == "great-grandmother");
    CHECK(T->relation("Rivka") == "grandmother");
    CHECK(T->relation("Betuel") == "great-grandfather");
    CHECK(T->relation("Rachel") == "mother");

    CHECK(T->relation("Lavan") == "grandfather");
    CHECK(T->relation("Haran") == "great-great-grandfather");
    CHECK(T->relation("Nahor") == "great-great-grandfather");
    CHECK(T->relation("Milca") == "great-great-grandmother"); 

    delete T;
}

TEST_CASE("find") {
    Tree *T;
    CHECK_NOTHROW(T = test_tree());

    CHECK(T->find("me") == "Yosef"); 
    CHECK(T->find("father") == "Yaakov"); 
    CHECK(T->find("mother") == "Rachel"); 

    string grandfather;
    CHECK_NOTHROW(grandfather = T->find("grandfather"));
    CHECK((grandfather == "Isaac" ||
           grandfather == "Lavan")); 

    CHECK(T->find("grandmother") == "Rivka");

    string great_grandfather;
    CHECK_NOTHROW(great_grandfather = T->find("great-grandfather")); 
    CHECK((great_grandfather == "Avraham" ||
           great_grandfather == "Betuel")); 

    CHECK(T->find("great-grandmother") == "Sara"); 

    string great_great_grandfather;
    CHECK_NOTHROW(great_great_grandfather = T->find("great-great-grandfather")); 
    CHECK((great_great_grandfather == "Terah" ||
           great_great_grandfather == "Haran" || 
           great_great_grandfather == "Nahor")); 

    CHECK(T->find("great-great-grandmother") == "Milca"); 
   
    CHECK_THROWS(T->find("brother")); // not define
    CHECK_THROWS(T->find("great-great-great-grandfather")); // not exist
    CHECK_THROWS(T->find("Sara")); // not a rilation
    delete T;
}



TEST_CASE("remove function") {
    Tree *T;
    CHECK_NOTHROW(T = test_tree());

    CHECK_THROWS(T->remove("Yosef")); // cant remove root
 
    CHECK_THROWS(T->remove("Dani")); // cant remove unexist 

    CHECK_NOTHROW(T->remove("Betuel"));

    CHECK(T->relation("Betuel") == "unrelated");
    CHECK(T->relation("Nahor") == "unrelated");
    CHECK(T->relation("Milca") == "unrelated");

    CHECK_THROWS(T->remove("Betuel")); // already removed 
    CHECK_THROWS(T->remove("Nahor")); // already removed 
    CHECK_THROWS(T->remove("Milca")); // already removed 


    CHECK_NOTHROW(T->remove("Haran"));
    CHECK(T->relation("Haran") == "unrelated");
    CHECK_THROWS(T->remove("Haran")); // already removed 


    CHECK_NOTHROW(T->remove("Lavan"));
    CHECK(T->relation("Lavan") == "unrelated");
    CHECK_THROWS(T->remove("Lavan")); // already removed 

    CHECK_NOTHROW(T->remove("Terah"));
    CHECK(T->relation("Terah") == "unrelated");
    CHECK_THROWS(T->remove("Terah")); // already removed 

    CHECK_NOTHROW(T->remove("Sara"));
    CHECK(T->relation("Sara") == "unrelated");
    CHECK_THROWS(T->remove("Sara")); // already removed 

    CHECK_NOTHROW(T->remove("Avraham"));
    CHECK(T->relation("Avraham") == "unrelated");
    CHECK_THROWS(T->remove("Avraham")); // already removed 

    CHECK_NOTHROW(T->remove("Rivka"));
    CHECK(T->relation("Rivka") == "unrelated");
    CHECK_THROWS(T->remove("Rivka")); // already removed 

    CHECK_NOTHROW(T->remove("Isaac"));
    CHECK(T->relation("Isaac") == "unrelated");
    CHECK_THROWS(T->remove("Isaac")); // already removed 

    CHECK_NOTHROW(T->remove("Rachel"));
    CHECK(T->relation("Rachel") == "unrelated");
    CHECK_THROWS(T->remove("Rachel")); // already removed 

    CHECK_NOTHROW(T->remove("Yaakov"));
    CHECK(T->relation("Yaakov") == "unrelated");
    CHECK_THROWS(T->remove("Yaakov")); // already removed 

    delete T;
}

//TEST_CASE("const tree") {
//    const Tree T("Adam");
//
//    //T.addFather("Terah", "bla"); // will not compile. not a const function.
//    //T.addFather("Terah", "bla"); // will not compile. not a const function.
//    //T.remove("Isaac"); // will not compile. not a const function.
//    CHECK_NOTHROW(T.display());
//    CHECK(T.find("me") == "Adam");
//    CHECK(T.relation("Adam") == "me");
//}
