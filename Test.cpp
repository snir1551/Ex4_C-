#include "doctest.h"
#include <string.h>
#include "FamilyTree.hpp"
using namespace family;
using namespace std;


TEST_CASE("Test add father and use find") {
    Tree T1("Yosef");
    string name_father = "Yoseff";
    string name_child = "Yosef";
    string name_grandfather = "grandfather";
    string search_name = "";
    T1.addFather(name_child,name_father);
    CHECK(T1.find("father") == name_father);
    for(int i = 0; i<15; i++)
    {
        name_child += "f"; 
        name_father += "f";
        int count = i;
        search_name = "";
        while(count!= 0)
        {
            search_name += "great-";
            count--;
        }
        search_name += name_grandfather;
        T1.addFather(name_child,name_father); // Tells the tree that the father of Yosef+(some of 'f') is Yosef+(some of 'f')+'f'.
        CHECK(T1.find(search_name) == name_father);
    }

}

TEST_CASE("Test add mother and find")
{
    Tree T1("Sara");
    string name_mother = "Saraw";
    string name_child = "Sara";
    string name_grandmother = "grandmother";
    string search_name = "";
    T1.addMother(name_child,name_mother);
    CHECK(T1.find("mother") == name_mother);
    for(int i = 0; i<15; i++)
    {
        name_child += "w";
        name_mother += "w";
        int count = i;
        search_name = "";
        while(count!= 0)
        {
            search_name += "great-";
            count--;
        }
        search_name += name_grandmother;
        T1.addMother(name_child,name_mother);
        CHECK(T1.find(search_name) == name_mother);
    }
    

}

TEST_CASE("Test add mother and add father (balanced tree) part 1")
{
    Tree T1("Yosef");
    T1.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")   // Tells the tree that the father of Yaakov is Isaac.
	 .addMother("Yaakov", "Rivka")   // Tells the tree that the mother of Yaakov is Rivka.
	 .addFather("Isaac", "Avraham")  // Tells the tree that the father of Isaac is Avraham.
	 .addMother("Isaac", "Sara"); // Tells the tree that the father of Avraham is Sara.

     CHECK(T1.find("father") == "Yaakov");
     CHECK(T1.find("mother") == "Rachel");
     CHECK(T1.find("grandfather") == "Isaac");
     CHECK(T1.find("grandmother") == "Rivka");
     CHECK(T1.find("great-grandfather") == "Avraham");
     CHECK(T1.find("great-grandmother") == "Sara");
     

}

TEST_CASE("Test add mother and add father")
{
    Tree T1("Roni");
    T1.addFather("Roni", "Miki")   // Tells the tree that the father of Roni is Miki.
	 .addMother("Roni", "Rut")   // Tells the tree that the mother of Roni is Rut.
	 .addFather("Rut", "David")   // Tells the tree that the father of Rut is David.
     .addFather("Miki", "Adi");    // Tells the tree that the father of Miki is Adi.
    
     CHECK(T1.find("me") == "Roni"); // me = Roni
     CHECK(T1.find("father") == "Miki"); // father of Roni is Miki
     CHECK(T1.find("mother") == "Rut"); // mother of Roni is Rut
     CHECK((T1.find("grandfather") == "Adi" || T1.find("grandfather") == "David")); // grandfather of Ronni is Adi or David

}

TEST_CASE("Test find")
{
    Tree T1("Yosef");
    T1.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	.addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	.addFather("Yaakov", "Isaac")   // Tells the tree that the father of Yaakov is Isaac.
	.addMother("Yaakov", "Rivka")   // Tells the tree that the mother of Yaakov is Rivka.
	.addFather("Isaac", "Avraham")  // Tells the tree that the father of Isaac is Avraham.
	.addMother("Isaac", "Sara")
    .addFather("Avraham", "Terah"); // Tells the tree that the father of Avraham is Sara.
    string findTheName = T1.find("me");
    CHECK(findTheName == "Yosef");
    findTheName = T1.find("father");
    CHECK(findTheName == "Yaakov");
    findTheName = T1.find("mother");
    CHECK(findTheName == "Rachel");
    findTheName = T1.find("grandfather");
    CHECK(findTheName == "Isaac");
    findTheName = T1.find("grandmother");
    CHECK(findTheName == "Rivka");
    findTheName = T1.find("great-grandfather");
    CHECK(findTheName == "Avraham");
    findTheName = T1.find("great-grandmother");
    CHECK(findTheName == "Sara");
    findTheName = T1.find("great-great-grandfather");
    CHECK(findTheName == "Terah");

    Tree T2("Yosef");
    T2.addFather("Yosef", "Yaakov")  
	 .addMother("Yosef", "Rachel")   
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

     CHECK(T2.find("me") != "Yaakov");
     CHECK(T2.find("me") != "Rachel");
     CHECK(T2.find("me") != "Isaac");
     CHECK(T2.find("me") != "Rivka");
     CHECK(T2.find("me") != "Avraham");
     CHECK(T2.find("me") != "Terah");

     CHECK(T2.find("father") != "Yosef");
     CHECK(T2.find("father") != "Rachel");
     CHECK(T2.find("father") != "Isaac");
     CHECK(T2.find("father") != "Rivka");
     CHECK(T2.find("father") != "Avraham");
     CHECK(T2.find("father") != "Terah");

     CHECK(T2.find("grandfather") != "Yosef");
     CHECK(T2.find("grandfather") != "Yaakov");
     CHECK(T2.find("grandfather") != "Rachel");
     CHECK(T2.find("grandfather") != "Rivka");
     CHECK(T2.find("grandfather") != "Avraham");
     CHECK(T2.find("grandfather") != "Terah");

     CHECK(T2.find("mother") != "Yosef");
     CHECK(T2.find("mother") != "Yaakov");
     CHECK(T2.find("mother") != "Isaac");
     CHECK(T2.find("mother") != "Rivka");
     CHECK(T2.find("mother") != "Avraham");
     CHECK(T2.find("mother") != "Terah");

     CHECK(T2.find("grandmother") != "Yosef");
     CHECK(T2.find("grandmother") != "Rachel");
     CHECK(T2.find("grandmother") != "Yaakov");
     CHECK(T2.find("grandmother") != "Isaac");
     CHECK(T2.find("grandmother") != "Avraham");
     CHECK(T2.find("grandmother") != "Terah");

     CHECK(T2.find("great-grandfather") != "Yosef");
     CHECK(T2.find("great-grandfather") != "Rachel");
     CHECK(T2.find("great-grandfather") != "Yaakov");
     CHECK(T2.find("great-grandfather") != "Isaac");
     CHECK(T2.find("great-grandfather") != "Rivka");
     CHECK(T2.find("great-grandfather") != "Terah");

     CHECK(T2.find("great-great-grandfather") != "Yosef");
     CHECK(T2.find("great-great-grandfather") != "Rachel");
     CHECK(T2.find("great-great-grandfather") != "Yaakov");
     CHECK(T2.find("great-great-grandfather") != "Isaac");
     CHECK(T2.find("great-great-grandfather") != "Rivka");
     CHECK(T2.find("great-great-grandfather") != "Avraham");

}

TEST_CASE("Test some fathers or some mothers exceptions")
{
    Tree T1("Yossi");
    CHECK_THROWS(T1.addFather("Yossi","David").addFather("Yossi","Shimon"));
    CHECK_THROWS(T1.addFather("Yossi","David").addMother("Yossi","leh").addFather("David","shimon").addMother("shimon","rebeka").addFather("David","haim").addMother("haim","ortal"));
    CHECK_THROWS(T1.addMother("Yossi","Rachel").addMother("Yossi","leh"));
}

TEST_CASE("Test find exceptions")
{
    Tree T1("Hola");
    CHECK_THROWS(T1.find("father"));
    CHECK_THROWS(T1.find("mother"));
    T1.addFather("Hola","Golan");
    T1.addFather("Golan","Ronen");
    CHECK_THROWS(T1.find("mother"));
    CHECK_THROWS(T1.find("grandmother"));

    Tree T2("Yosef");
    T2.addFather("Yosef", "Yaakov")  
	 .addMother("Yosef", "Rachel")   
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

     

     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));
     CHECK_THROWS(T2.find("great-grandmother"));

     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));
     CHECK_THROWS(T2.find("great-great-grandmother"));

     CHECK_THROWS(T2.find(""));
     CHECK_THROWS(T2.find(" "));
     CHECK_THROWS(T2.find("  "));
     CHECK_THROWS(T2.find("                  "));
     CHECK_THROWS(T2.find(" great-great-grandfather"));
     CHECK_THROWS(T2.find("great-great-grandfather "));
     CHECK_THROWS(T2.find("      great-great-grandfather         "));
     CHECK_THROWS(T2.find(" gread-gread-grandfather"));
     CHECK_THROWS(T2.find("gread-gread-grandfather"));
     CHECK_THROWS(T2.find("great-gread-grandfather"));
     CHECK_THROWS(T2.find("gread-great-grandfather"));
     CHECK_THROWS(T2.find("great-great-grantfather"));
     CHECK_THROWS(T2.find("great-great-greatfather"));
     CHECK_THROWS(T2.find("g-g-grandfather"));

     CHECK_THROWS(T2.find("grantfather"));
     CHECK_THROWS(T2.find(" grandfather"));
     CHECK_THROWS(T2.find("grandfather "));
     CHECK_THROWS(T2.find("   grandfather    "));
     
    CHECK_THROWS(T2.find("   father    "));
    CHECK_THROWS(T2.find(" father"));
    CHECK_THROWS(T2.find("father "));

    CHECK_THROWS(T2.find("   mother    "));
    CHECK_THROWS(T2.find(" mother"));
    CHECK_THROWS(T2.find("mother "));

    CHECK_THROWS(T2.find("   me     "));
    CHECK_THROWS(T2.find("  me"));
    CHECK_THROWS(T2.find("me  "));


}

TEST_CASE("Test relation")
{
    Tree T1("Yosef");
    T1.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")   // Tells the tree that the father of Yaakov is Isaac.
	 .addMother("Yaakov", "Rivka")   // Tells the tree that the mother of Yaakov is Rivka.
	 .addFather("Isaac", "Avraham")  // Tells the tree that the father of Isaac is Avraham.
	 .addMother("Isaac", "Sara"); // Tells the tree that the father of Avraham is Sara.

     string nameRelation = T1.relation("Yosef");
     CHECK(nameRelation == "me");
     nameRelation = T1.relation("Yaakov");
     CHECK(nameRelation == "father");
     nameRelation = T1.relation("Rachel");
     CHECK(nameRelation == "mother");
     nameRelation = T1.relation("Isaac");
     CHECK(nameRelation == "grandfather");
     nameRelation = T1.relation("Rivka");
     CHECK(nameRelation == "grandmother");
     nameRelation = T1.relation("Avraham");
     CHECK(nameRelation == "great-grandfather");
     nameRelation = T1.relation("Sara");
     CHECK(nameRelation == "great-grandmother");
     

    Tree T2("Yosef");
    T2.addFather("Yosef", "Yaakov")  
	 .addMother("Yosef", "Rachel")   
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

     CHECK(T2.relation("Yosef") == "me");
     CHECK(T2.relation("Yosef") != "father");
     CHECK(T2.relation("Yosef") != "grandfather");
     CHECK(T2.relation("Yosef") != "mother");
     CHECK(T2.relation("Yosef") != "grandmother");
     CHECK(T2.relation("Yosef") != "great-grandfather");
     CHECK(T2.relation("Yosef") != "great-grandmother");

     CHECK(T2.relation("Yaakov") == "father");
     CHECK(T2.relation("Yaakov") != "me");
     CHECK(T2.relation("Yaakov") != "grandfather");
     CHECK(T2.relation("Yaakov") != "mother");
     CHECK(T2.relation("Yaakov") != "grandmother");
     CHECK(T2.relation("Yaakov") != "great-grandfather");
     CHECK(T2.relation("Yaakov") != "great-grandmother");
     
     CHECK(T2.relation("Rachel") == "mother");
     CHECK(T2.relation("Rachel") != "me");
     CHECK(T2.relation("Rachel") != "grandfather");
     CHECK(T2.relation("Rachel") != "father");
     CHECK(T2.relation("Rachel") != "grandmother");
     CHECK(T2.relation("Rachel") != "great-grandfather");
     CHECK(T2.relation("Rachel") != "great-grandmother");

     CHECK(T2.relation("Isaac") == "grandfather");
     CHECK(T2.relation("Isaac") != "me");
     CHECK(T2.relation("Isaac") != "mother");
     CHECK(T2.relation("Isaac") != "father");
     CHECK(T2.relation("Isaac") != "grandmother");
     CHECK(T2.relation("Isaac") != "great-grandfather");
     CHECK(T2.relation("Isaac") != "great-grandmother");

     CHECK(T2.relation("Rivka") == "grandmother");
     CHECK(T2.relation("Rivka") != "me");
     CHECK(T2.relation("Rivka") != "mother");
     CHECK(T2.relation("Rivka") != "father");
     CHECK(T2.relation("Rivka") != "grandfather");
     CHECK(T2.relation("Rivka") != "great-grandfather");
     CHECK(T2.relation("Rivka") != "great-grandmother");
     
     CHECK(T2.relation("Avraham") == "great-grandfather");
     CHECK(T2.relation("Avraham") != "me");
     CHECK(T2.relation("Avraham") != "mother");
     CHECK(T2.relation("Avraham") != "father");
     CHECK(T2.relation("Avraham") != "grandfather");
     CHECK(T2.relation("Avraham") != "grandmother");
     CHECK(T2.relation("Avraham") != "great-grandmother");

     CHECK(T2.relation("Terah") == "great-great-grandfather");
     CHECK(T2.relation("Terah") != "me");
     CHECK(T2.relation("Terah") != "mother");
     CHECK(T2.relation("Terah") != "father");
     CHECK(T2.relation("Terah") != "grandfather");
     CHECK(T2.relation("Terah") != "grandmother");
     CHECK(T2.relation("Terah") != "great-grandmother");
     


      
}

TEST_CASE("Test unrelated in relation")
{
    

    Tree T2("Yosef");
    T2.addFather("Yosef", "Yaakov")  
	 .addMother("Yosef", "Rachel")   
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

     CHECK(T2.relation("terah") == "unrelated");
     CHECK(T2.relation(" Terah") == "unrelated");
     CHECK(T2.relation("  Terah  ") == "unrelated");
     CHECK(T2.relation("Terah ") == "unrelated");

     CHECK(T2.relation("avraham") == "unrelated");
     CHECK(T2.relation(" Avraham") == "unrelated");
     CHECK(T2.relation("  Avraham  ") == "unrelated");
     CHECK(T2.relation("Avraham ") == "unrelated");

     CHECK(T2.relation("isaac") == "unrelated");
     CHECK(T2.relation(" Isaac") == "unrelated");
     CHECK(T2.relation("  Isaac  ") == "unrelated");
     CHECK(T2.relation("Isaac ") == "unrelated");

     CHECK(T2.relation("yaakov") == "unrelated");
     CHECK(T2.relation("  Yaakov") == "unrelated");
     CHECK(T2.relation("  Yaakov  ") == "unrelated");
     CHECK(T2.relation("Yaakov ") == "unrelated");

     CHECK(T2.relation("rivka") == "unrelated");
     CHECK(T2.relation("  Rivka") == "unrelated");
     CHECK(T2.relation("  Rivka  ") == "unrelated");
     CHECK(T2.relation("Rivka ") == "unrelated");

     CHECK(T2.relation("rachel") == "unrelated");
     CHECK(T2.relation("  Rachel") == "unrelated");
     CHECK(T2.relation("  Rachel  ") == "unrelated");
     CHECK(T2.relation("Rachel ") == "unrelated");

     CHECK(T2.relation("yosef") == "unrelated");
     CHECK(T2.relation("   Yosef") == "unrelated");
     CHECK(T2.relation("  Yosef  ") == "unrelated");
     CHECK(T2.relation("Yosef ") == "unrelated");


}

TEST_CASE("Test remove")
{
    Tree T2("Dani");
    T2.addFather("Dani", "Asaf")  
	 .addMother("Dani", "Maksima")   
	 .addFather("Asaf", "Ronen")
	 .addMother("Asaf", "Rivka")
	 .addFather("Ronen", "Avraham")
	 .addFather("Avraham", "mashlim")
     .addFather("mashlim","Gadi")
     .addMother("mashlim","Shushan")
     .addFather("Gadi","Yogev");
     

     CHECK(T2.relation("Dani") == "me");
     CHECK(T2.relation("Asaf") == "father");
     CHECK(T2.relation("Maksima") == "mother");
     CHECK(T2.relation("Ronen") == "grandfather");
     CHECK(T2.relation("Rivka") == "grandmother");
     CHECK(T2.relation("Avraham") == "great-grandfather");
     CHECK(T2.relation("mashlim") == "great-great-grandfather");
     CHECK(T2.relation("Gadi") == "great-great-great-grandfather");
     CHECK(T2.relation("Shushan") == "great-great-great-grandmother");
     CHECK(T2.relation("Yogev") == "great-great-great-great-grandfather");

     T2.remove("Avraham");
     
     CHECK(T2.relation("Dani") == "me");
     CHECK(T2.relation("Asaf") == "father");
     CHECK(T2.relation("Maksima") == "mother");
     CHECK(T2.relation("Ronen") == "grandfather");
     CHECK(T2.relation("Rivka") == "grandmother");

     CHECK(T2.relation("Avraham") == "unrelated");
     CHECK(T2.relation("mashlim") == "unrelated");
     CHECK(T2.relation("Gadi") == "unrelated");
     CHECK(T2.relation("Shushan") == "unrelated");
     CHECK(T2.relation("Yogev") == "unrelated");


     T2.addFather("Ronen", "Avraham")
	 .addFather("Avraham", "mashlim")
     .addFather("mashlim","Gadi")
     .addMother("mashlim","Shushan")
     .addFather("Gadi","Yogev");

    T2.remove("Asaf");

     CHECK(T2.relation("Dani") == "me");
     CHECK(T2.relation("Asaf") == "unrelated");
     CHECK(T2.relation("Maksima") == "mother");
     CHECK(T2.relation("Ronen") == "unrelated");
     CHECK(T2.relation("Rivka") == "unrelated");
     CHECK(T2.relation("Avraham") == "unrelated");
     CHECK(T2.relation("mashlim") == "unrelated");
     CHECK(T2.relation("Gadi") == "unrelated");
     CHECK(T2.relation("Shushan") == "unrelated");
     CHECK(T2.relation("Yogev") == "unrelated");

     T2.addFather("Dani", "Asaf")  
       .addFather("Asaf", "Ronen")
	   .addMother("Asaf", "Rivka")
	   .addFather("Ronen", "Avraham")
	   .addFather("Avraham", "mashlim")
       .addFather("mashlim","Gadi")
       .addMother("mashlim","Shushan")
       .addFather("Gadi","Yogev");

     CHECK(T2.relation("Dani") == "me");
     CHECK(T2.relation("Asaf") == "father");
     CHECK(T2.relation("Maksima") == "mother");
     CHECK(T2.relation("Ronen") == "grandfather");
     CHECK(T2.relation("Rivka") == "grandmother");
     CHECK(T2.relation("Avraham") == "great-grandfather");
     CHECK(T2.relation("mashlim") == "great-great-grandfather");
     CHECK(T2.relation("Gadi") == "great-great-great-grandfather");
     CHECK(T2.relation("Shushan") == "great-great-great-grandmother");
     CHECK(T2.relation("Yogev") == "great-great-great-great-grandfather");



}


TEST_CASE("Test remove exception")
{
    Tree T2("Dani");
    T2.addFather("Dani", "Asaf")  
	 .addMother("Dani", "Maksima")   
	 .addFather("Asaf", "Ronen")
	 .addMother("Asaf", "Rivka")
	 .addFather("Ronen", "Avraham")
	 .addFather("Avraham", "mashlim")
     .addFather("mashlim","Gadi")
     .addMother("mashlim","Shushan")
     .addFather("Gadi","Yogev")
     .addMother("Shushan","lilach");

     CHECK_THROWS(T2.remove("Golan"));
     CHECK_THROWS(T2.remove("Asa"));
     CHECK_THROWS(T2.remove("asaf"));
     CHECK_THROWS(T2.remove("ASaf"));
     CHECK_THROWS(T2.remove("Dani"));

}

TEST_CASE("Complex Test")
{
    Tree T2("Dani");
    T2.addFather("Dani", "Asaf")  
	 .addMother("Dani", "Maksima")   
	 .addFather("Asaf", "Ronen")
	 .addMother("Asaf", "Rivka")
	 .addFather("Ronen", "Avraham")
	 .addFather("Avraham", "mashlim")
     .addFather("mashlim","Gadi")
     .addMother("mashlim","Shushan")
     .addFather("Gadi","Yogev")
     .addMother("Shushan","lilach");

     string findSearch1 = T2.find("father"); // Asaf
     string relationSearch1 = T2.relation("Asaf"); // father
     string findSearch2 = T2.find(relationSearch1); // Asaf
     string relationSearch2 = T2.relation(findSearch1); // father

     CHECK(findSearch1 == "Asaf");
     CHECK(relationSearch1 == "father");
     CHECK(findSearch2 == "Asaf");
     CHECK(relationSearch1 == "father");

     CHECK_THROWS(T2.remove("Dani"));
     T2.remove("Asaf");
     CHECK_THROWS(T2.find(relationSearch1)); // Asaf
     string relationSearch3 = T2.relation(findSearch1); // father
     CHECK(relationSearch3 == "unrelated");

     Tree T3("Gadi");
     T3.addFather("Gadi","Haim")
       .addFather("Haim","Moshe")
       .addFather("Moshe","Meshulam")
       .addFather("Meshulam","Shimshon")
       .addMother("Shimshon","zafrit")
       .addFather("Shimshon","ShimshonI")
       .addMother("zafrit","zohar")
       .addMother("zohar","zomer")
       .addFather("zomer","hatuka");

     

     CHECK(T3.find("me") == "Gadi");
     CHECK(T3.find("father") == "Haim");
     CHECK(T3.find("grandfather") == "Moshe");
     CHECK(T3.find("great-grandfather") == "Meshulam");
     CHECK(T3.find("great-great-grandfather") == "Shimshon");
     CHECK(T3.find("great-great-great-grandmother") == "zafrit");
     CHECK(T3.find("great-great-great-great-grandmother") == "zohar");
     CHECK(T3.find("great-great-great-great-great-grandmother") == "zomer");
     CHECK(T3.find("great-great-great-great-great-great-grandfather") == "hatuka");

     T3.remove("hatuka");

     CHECK(T3.find("me") == "Gadi");
     CHECK(T3.find("father") == "Haim");
     CHECK(T3.find("grandfather") == "Moshe");
     CHECK(T3.find("great-grandfather") == "Meshulam");
     CHECK(T3.find("great-great-grandfather") == "Shimshon");
     CHECK(T3.find("great-great-great-grandmother") == "zafrit");
     CHECK(T3.find("great-great-great-great-grandmother") == "zohar");
     CHECK(T3.find("great-great-great-great-great-grandmother") == "zomer");
     CHECK(T3.relation("hatuka") == "unrelated");

     T3.addFather("zomer","hatuka");
     T3.remove("ShimshonI");

     CHECK(T3.find("me") == "Gadi");
     CHECK(T3.find("father") == "Haim");
     CHECK(T3.find("grandfather") == "Moshe");
     CHECK(T3.find("great-grandfather") == "Meshulam");
     CHECK(T3.find("great-great-grandfather") == "Shimshon");
     CHECK(T3.find("great-great-great-grandmother") == "zafrit");
     CHECK(T3.find("great-great-great-great-grandmother") == "zohar");
     CHECK(T3.find("great-great-great-great-great-grandmother") == "zomer");
     CHECK(T3.find("great-great-great-great-great-great-grandfather") == "hatuka");
     CHECK(T3.relation("ShimshonI") == "unrelated");



}

TEST_CASE("Find Test Exception Message")
{
    Tree T1("Yosef");
    try
    {
        T1.find("C++");
    }
    catch(exception& ex)
    {
        CHECK(strcmp(ex.what(), "The tree cannot handle the 'C++' relation") == 0);
    }
    try
    {
        T1.find("C++ = C + JAVA");
    }
    catch(exception& ex)
    {
        CHECK(strcmp(ex.what(), "The tree cannot handle the 'C++ = C + JAVA' relation") == 0);
    }
}