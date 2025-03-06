#include <iostream>
#include "math.h"


int main() {
    // Luodaan testivektorit
    math::vec2 v1 = math::vec(1.0f, 2.0f);
    math::vec2 v2 = math::vec(3.0f, 4.0f);

    math::vec2 v3 = math::vec(23.0f, 34.0f);
    math::vec2 v4 = math::vec(13.0f, 64.0f); 

    math::vec2 v5 = math::vec(0.098f, 54.0f);
    math::vec2 v6 = math::vec(0.0035f, 0.1f);

    //Luodan vektorit 3D
    math::vec3 v1_3D = math::vec(1.0f, 2.0f, 3.0f);
    math::vec3 v2_3D = math::vec(4.0f, 5.0f, 6.0f);

    math::vec3 v3_3D = math::vec(12.0f, 21.0f, 36.0f);
    math::vec3 v4_3D = math::vec(34.06f, 15.04f, 56.08f);

    math::vec3 v5_3D = math::vec(8.20f, 9.30f, 4.04f);
    math::vec3 v6_3D = math::vec(43.0f, 51.0f, 86.0f);

    // 1 Lasketaan vektorien summa
    math::vec2 sum_vec2 = math::add(v1, v2);
    math::vec2 sum_vec3 = math::add(v3, v4);
    math::vec2 sum_vec4 = math::add(v5, v6);

    std::cout << "Summa ero sum_vec2: " << math::to_string(sum_vec2) << std::endl;
    math::vec2 rightSum;
    rightSum[0] = 1.0f + 3.0f;
    rightSum[1] = 2.0f + 4.0f;
    if (sum_vec2 != rightSum)
    {
        std::cout << "Test failed!" << math::to_string(sum_vec2) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-sum_vec2" << math::to_string(sum_vec2) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;
    math::vec2 rightSum3;
    rightSum3[0] = 23.0f + 13.0f;
    rightSum3[1] = 34.0f + 64.0f;
    // Antes de la comparación, agrega declaraciones de impresión 
    //"Before the comparison, add print statements."
    std::cout << "sum_vec3: " << math::to_string(sum_vec3) << std::endl;
    std::cout << "Caset_Sum3: " << math::to_string(rightSum3) << std::endl;

    // Luego, utiliza la función de comparación personalizada
    //"Afterwards, use the custom comparison function."
     if (math::areEqual(sum_vec3, rightSum3, 0.0001f)) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test failed!" << std::endl;
        return -1;
    }
     std::cout << "..................................................................!" << std::endl;

     math::vec2 rightSum4;
     rightSum4[0] = 0.098f + 0.0035f;
     rightSum4[1] = 54.0f + 0.1f;
     // Antes de la comparación, agrega declaraciones de impresión 
     //"Before the comparison, add print statements."
     std::cout << "sum_vec4: " << math::to_string(sum_vec4) << std::endl;
     std::cout << "Caset_Sum4: " << math::to_string(rightSum4) << std::endl;

     // Luego, utiliza la función de comparación personalizada
     //"Afterwards, use the custom comparison function."
     if (math::areEqual(sum_vec4, rightSum4, 0.0001f)) {
         std::cout << "Test PASSED!" << std::endl;
     }
     else {
         std::cout << "Test failed!" << std::endl;
         return -1;
     }
     std::cout <<"..................................................................!"<< std::endl;
     // 1 Lasketaan vektorien Vhennety 
     math::vec2 sub_vec2 = math::sub(v1, v2);
     math::vec2 sub_vec3 = math::sub(v3, v4);
     math::vec2 sub_vec4 = math::sub(v5, v6);

     std::cout << "Vhenny ero sub_vec2: " << math::to_string(sub_vec2) << std::endl;
     //Caset test comparation 
    math::vec2  rightdiff2;
    rightdiff2[0] = 1.0f - 3.0f;
    rightdiff2[1] = 2.0f - 4.0f;
    if (sub_vec2 != rightdiff2) {
        std::cout << "Test failed!" << math::to_string(sub_vec2) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-sub_vec2 " << math::to_string(sub_vec2) << std::endl;
        std::cout << "Test PASSED! " << std::endl;

    }
    std::cout <<"..................................................................!"<< std::endl;
    std::cout << "Vhenny ero sub_vec3: " << math::to_string(sub_vec3) << std::endl;
    math::vec2  rightdiff3;
    rightdiff3[0] = 23.0f - 13.0f;
    rightdiff3[1] = 34.0f - 64.0f;
    if (sub_vec3 != rightdiff3) {
        std::cout << "Test failed!" << math::to_string(sub_vec3) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-sub_vec3" << math::to_string(sub_vec3) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout <<"..................................................................!"<< std::endl;
    math::vec2 rightdiff4;
    rightdiff4[0] = 0.098f - 0.0035f;
    rightdiff4[1] = 54.0f - 0.1f;
    // Antes de la comparación, agrega declaraciones de impresión 
    //"Before the comparison, add print statements."
    std::cout << "Vhenny ero sub_vec4: " << math::to_string(sub_vec4) << std::endl;
    std::cout << "Caset_Sub4: " << math::to_string(rightdiff4) << std::endl;

    // Luego, utiliza la función de comparación personalizada
    //"Afterwards, use the custom comparison function."
    if (math::areEqual(sub_vec4, rightdiff4, 0.0001f)) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test failed!" << std::endl;
        return -1;
    }
    std::cout <<"..................................................................!" << std::endl;
    // 2 laske Vektorien summa 3D
    math::vec3 sum2_3D = math::add(v1_3D, v2_3D);
    math::vec3 sum3_3D = math::add(v3_3D, v4_3D);
    math::vec3 sum4_3D = math::add(v5_3D, v6_3D);

    std::cout << "Summa ero v1_3D ja v2_3D: " << math::to_string(sum2_3D) << std::endl;
    math::vec3 rightSub2;
    rightSub2[0] = 1.0f + 4.0f;
    rightSub2[1] = 2.0f + 5.0f;
    rightSub2[2] = 3.0f + 6.0f;
    if (sum2_3D != rightSub2)
    {
        std::cout << "Test failed!" << math::to_string(sum2_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-sum2_3D:" << math::to_string(sum2_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout <<"..................................................................!"<< std::endl;

    std::cout << "Summa ero v3_3D ja v4_3D: " << math::to_string(sum3_3D) << std::endl;
    math::vec3 rightSub3;
    rightSub3[0] = 12.0f + 34.06f;
    rightSub3[1] = 21.0f + 15.04f;
    rightSub3[2] = 36.0f + 56.08f;
    if (sum3_3D != rightSub3)
    {
        std::cout << "Test failed!" << math::to_string(sum3_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-sum3_3D:" << math::to_string(sum3_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout <<"..................................................................!"<< std::endl;

    math::vec3 rightSub4;
    rightSub4[0] = 8.20f + 43.0f;
    rightSub4[1] = 9.30f + 51.0f;
    rightSub4[2] = 4.04f + 86.0f;
    // Antes de la comparación, agrega declaraciones de impresión 
    //"Before the comparison, add print statements."
    std::cout << "Summa ero v5_3D ja v6_3D:: " << math::to_string(sum4_3D) << std::endl;
    std::cout << "Caset_sum4_3D: " << math::to_string(rightSub4) << std::endl;

    // Luego, utiliza la función de comparación personalizada
    //"Afterwards, use the custom comparison function."
    if (math::areEqual(sum4_3D, rightSub4, 0.0001f)) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test failed!" << std::endl;
        return -1;
    }
    std::cout << "..................................................................!" << std::endl;

    // laske Vektorien Vahenny 3D
    math::vec3 diff2_3D = math::sub(v1_3D, v2_3D);
    math::vec3 diff3_3D = math::sub(v3_3D, v4_3D);
    math::vec3 diff4_3D = math::sub(v5_3D, v6_3D);

    std::cout << "Vhenny ero v1_3D ja v2_3D: " << math::to_string(diff2_3D) << std::endl;
    math::vec3 DiffSub2;
    DiffSub2[0] = 1.0f - 4.0f;
    DiffSub2[1] = 2.0f - 5.0f;
    DiffSub2[2] = 3.0f - 6.0f;
    if (diff2_3D != DiffSub2)
    {
        std::cout << "Test failed!" << math::to_string(diff2_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-diff2_3D:" << math::to_string(diff2_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Vhenny ero v2_3D ja v3_3D:: " << math::to_string(diff3_3D) << std::endl;
    math::vec3 DiffSub3;
    DiffSub3[0] = 12.0f - 34.06f;
    DiffSub3[1] = 21.0f - 15.04f;
    DiffSub3[2] = 36.0f - 56.08f;
    if (diff3_3D != DiffSub3)
    {
        std::cout << "Test failed!" << math::to_string(diff3_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-diff3_3D:" << math::to_string(diff3_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Vhenny ero v5_3D ja v6_3D:: " << math::to_string(diff4_3D) << std::endl;
    math::vec3 DiffSub4;
    DiffSub4[0] = 8.20f - 43.0f;
    DiffSub4[1] = 9.30f - 51.0f;
    DiffSub4[2] = 4.04f - 86.0f;
    if (diff4_3D != DiffSub4)
    {
        std::cout << "Test failed!" << math::to_string(diff4_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-diff3_3D:" << math::to_string(diff4_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    // 3 Lasketaan vektorin v1 ja skalaarin 2 tulot
    math::vec2 scaled_vec2 = math::mul(2.0f, v1);
    math::vec2 scaled_vec3 = math::mul(5.0f, v3);
    math::vec2 scaled_vec4 = math::mul(0.0080f, v6);

    std::cout << "Skalaarin tulos v1 : " << math::to_string(scaled_vec2) << std::endl;
    math::vec2 scaled2;
    scaled2[0] = 2 * 1.0f;
    scaled2[1] = 2 * 2.0f;
    if (scaled2 != scaled_vec2)
    {
        std::cout << "Test failed!" << math::to_string(scaled_vec2) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled_vec2:" << math::to_string(scaled_vec2) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Skalaarin tulos v3 : " << math::to_string(scaled_vec3) << std::endl;
    math::vec2 scaled3;
    scaled3[0] = 5 * 23.0f;
    scaled3[1] = 5 * 34.0f;
    if (scaled3 != scaled_vec3)
    {
        std::cout << "Test failed!" << math::to_string(scaled_vec3) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled_vec3:" << math::to_string(scaled_vec3) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;
  
    std::cout << "Skalaarin tulos v6 : " << math::to_string(scaled_vec4) << std::endl;
    math::vec2 scaled4;
    scaled4[0] = 0.0080f * 0.0035f;
    scaled4[1] = 0.0080f * 0.1f;
    if (scaled4 != scaled_vec4)
    {
        std::cout << "Test failed!" << math::to_string(scaled_vec4) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled_vec6:" << math::to_string(scaled_vec4) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    // 4 Lasketaan vektorin v2 ja jakajan 5 osamr
    math::vec2 divided_vec2 = math::div(v2, 5.0f); //    math::vec2 v2 = math::vec(3.0f, 4.0f);
    math::vec2 divided_vec3 = math::div(v4, 2.50f);//    math::vec2 v4 = math::vec(13.0f, 64.0f); 
    math::vec2 divided_vec4 = math::div(v5, 12.0f);//    math::vec2 v5 = math::vec(0.098f, 54.0f);

    std::cout << "Jakajan 5 osamr v2: " << math::to_string(divided_vec2) << std::endl;
    math::vec2 divides2;
    divides2[0] = 3.0f / 5.0f ;
    divides2[1] = 4.0f / 5.0f;
    if (divides2 != divided_vec2)
    {
        std::cout << "Test failed!" << math::to_string(divided_vec2) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided_vec2:" << math::to_string(divided_vec2) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Jakajan 2.50 osamr v4: " << math::to_string(divided_vec3) << std::endl;
    math::vec2 divides3;
    divides3[0] =  13.0f / 2.50f;
    divides3[1] =  64.0f / 2.50f;
    if (divides3 != divided_vec3)
    {
        std::cout << "Test failed!" << math::to_string(divided_vec3) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided_vec2:" << math::to_string(divided_vec3) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Jakajan 12.0f osamr v5: " << math::to_string(divided_vec4) << std::endl;
    math::vec2 divides4;
    divides4[0] = 0.098f / 12.0f;
    divides4[1] = 54.0f / 12.0f;
    if (divides4 != divided_vec4)
    {
        std::cout << "Test failed!" << math::to_string(divided_vec4) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided_vec4:" << math::to_string(divided_vec4) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    // 5 Lasketaan vektori v1_3D ja skalaarin 2 tulot
    math::vec3 scaled2_3D = math::mul(2.0f, v1_3D); // math::vec(1.0f, 2.0f, 3.0f);
    math::vec3 scaled3_3D = math::mul(9.0f, v3_3D); // math::vec(12.0f, 21.0f, 36.0f);
    math::vec3 scaled4_3D = math::mul(26.0f, v5_3D); // math::vec(8.20f, 9.30f, 4.04f);

    std::cout << "skalaarin v1_3D tulos: " << math::to_string(scaled2_3D) << std::endl;
    math::vec3 scaled13D;
    scaled13D[0] = 2.0f * 1.0f;
    scaled13D[1] = 2.0f * 2.0f;
    scaled13D[2] = 2.0f * 3.0f;
    if (scaled13D != scaled2_3D)
    {
        std::cout << "Test failed!" << math::to_string(scaled2_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled2_3D:" << math::to_string(scaled2_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "skalaarin v3_3D tulos: " << math::to_string(scaled3_3D) << std::endl;
    math::vec3 scaled23D;
    scaled23D[0] = 9.0f * 12.0f;
    scaled23D[1] = 9.0f * 21.0f;
    scaled23D[2] = 9.0f * 36.0f;
    if (scaled23D != scaled3_3D)
    {
        std::cout << "Test failed!" << math::to_string(scaled3_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled3_3D:" << math::to_string(scaled3_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "skalaarin v4_3D tulos: " << math::to_string(scaled4_3D) << std::endl;
    math::vec3 scaled33D;
    scaled33D[0] = 26.0f * 8.20f;
    scaled33D[1] = 26.0f * 9.30f;
    scaled33D[2] = 26.0f * 4.04f;
    if (scaled33D != scaled4_3D)
    {
        std::cout << "Test failed!" << math::to_string(scaled4_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-scaled4_3D:" << math::to_string(scaled4_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;
    // 6 Lasketaan vektorin v3 ja jakajan 5 osamr
    math::vec3 divided_3D = math::div(v2_3D, 5.0f); // math::vec(4.0f, 5.0f, 6.0f);
    math::vec3 divided1_3D = math::div(v4_3D, 2.25f); // math::vec(34.06f, 15.04f, 56.08f);
    math::vec3 divided2_3D = math::div(v6_3D, 15.0f); // math::vec(43.0f, 51.0f, 86.0f);

    std::cout << "Jakajan 5 osamra v2_3D ero: " << math::to_string(divided_3D) << std::endl;
    math::vec3 divided13D;
    divided13D[0] = 4.0f / 5.0f;
    divided13D[1] = 5.0f / 5.0f;
    divided13D[2] = 6.0f / 5.0f;
    if (divided13D != divided_3D)
    {
        std::cout << "Test failed!" << math::to_string(divided_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided_3D:" << math::to_string(divided_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Jakajan 2.25f osamra v4_3D ero: " << math::to_string(divided1_3D) << std::endl;
    math::vec3 divided23D;
    divided23D[0] = 34.06f / 2.25f;
    divided23D[1] = 15.04f / 2.25f;
    divided23D[2] = 56.08f / 2.25f;
    if (divided23D != divided1_3D)
    {
        std::cout << "Test failed!" << math::to_string(divided1_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided1_3D:" << math::to_string(divided1_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    std::cout << "Jakajan 15.0f osamra v4_3D ero: " << math::to_string(divided2_3D) << std::endl;
    math::vec3 divided33D;
    divided33D[0] = 43.0f / 15.0f;
    divided33D[1] = 51.0f / 15.0f;
    divided33D[2] = 86.0f / 15.0f;
    if (divided33D != divided2_3D)
    {
        std::cout << "Test failed!" << math::to_string(divided2_3D) << std::endl;
        return -1;
    }
    else {
        std::cout << "CasetTest-divided2_3D:" << math::to_string(divided2_3D) << std::endl;
        std::cout << "Test PASSED! " << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    //Mrittele kaksi 3D-vektoria.
    math::vec3 vector1 = math::vec(1.0f, 2.0f, 3.0f);
    math::vec3 vector2 = math::vec(4.0f, 5.0f, 6.0f);

    math::vec3 vector3 = math::vec(6.0f, 15.0f, 06.10f);
    math::vec3 vector4 = math::vec(42.0f, 65.0f, 76.0f);

    math::vec3 vector5 = math::vec(56.0f, 78.0f, 489.0f);
    math::vec3 vector6 = math::vec(657.0f, 4554.0f, 89894.0f);

    //Laske pistetulo
    float dotProduct = math::dot(vector1, vector2);

    // Tulosta tulos arvo.
    std::cout << " Arvo vector1 ja vector2 on: " << dotProduct << std::endl;

    float CaseDotProduct = 1.0f * 4.0f + 2.0f * 5.0f + 3.0f * 6.0f;
    std::cout << " Caset-DotProduct Test on: " << CaseDotProduct << std::endl;
    // Tarkista, si el resultado es igual al valor esperado.
    if (dotProduct == CaseDotProduct) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    //Laske pistetulo
    float dotProduct1 = math::dot(vector3, vector4); // math::vec(6.0f, 15.0f, 06.10f); 
                                                    //math::vec(42.0f, 65.0f, 76.0f);
                                                    // 
    // Tulosta tulos arvo.
    std::cout << " Arvo vector3 ja vector4 on: " << dotProduct1 << std::endl;

    float CaseDotProduct1 = 6.0f * 42.0f + 15.0f * 65.0f + 06.10f * 76.0f;
    std::cout << " Caset-DotProduct Test on: " << CaseDotProduct1 << std::endl;
    // Tarkista, si el resultado es igual al valor esperado.
    if (dotProduct1 == CaseDotProduct1) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    //Laske pistetulo
    float dotProduct2 = math::dot(vector5, vector6); // math::vec(56.0f, 78.0f, 489.0f);
                                                    //  math::vec(657.0f, 4554.0f, 89894.0f);
                                                    // 
    // Tulosta tulos arvo.
    std::cout << " Arvo vector3 ja vector4 on: " << dotProduct2 << std::endl;

    float CaseDotProduct2 = 56.0f * 657.0f + 78.0f * 4554.0f + 489.0f * 89894.0f;
    std::cout << " Caset-DotProduct Test on: " << CaseDotProduct2 << std::endl;
    // Tarkista, si el resultado es igual al valor esperado.
    if (dotProduct2 == CaseDotProduct2) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;


    // Determinante de una matriz 3x3
    math::mat3 matrix0 = math::mat(
        math::vec(1.0f, 2.0f, 3.0f),
        math::vec(4.0f, 5.0f, 6.0f),
        math::vec(7.0f, 8.0f, 9.0f)
    );
    float determinant0 = math::det(matrix0);
    float paperillaLaskettuDeterminantCaseen0 = 0.0f;
    std::cout << "Determinante on: " << determinant0 << std::endl;
    if(determinant0 == paperillaLaskettuDeterminantCaseen0) {
        std::cout << "Case Test Determinante on: " << determinant0 << std::endl;
        std::cout << "Test PASSED!" << std::endl;
    } else {
        std::cout << "Determinante NOT OK: " << determinant0 << std::endl;
        return -1;
    }
    std::cout << "..................................................................!" << std::endl;

    auto matrix1 = math::mat(
        math::vec(7,3,3),
        math::vec(4,3,6),
        math::vec(7,3,7)
    );
    float determinant1 = math::det(matrix1);
    float paperillaLaskettuDeterminantCaseen1 = 36.0f;
    std::cout << "Determinante on: " << determinant1 << std::endl;
    if(determinant1 == paperillaLaskettuDeterminantCaseen1) {
        std::cout << "Case Test Determinante on: " << determinant1 << std::endl;
        std::cout << "Test PASSED!" << std::endl;
    } else {
        std::cout << "Determinante NOT OK: " << determinant1 << std::endl;
        return -1;
    }
    std::cout << "..................................................................!" << std::endl;

    auto matrix2 = math::mat(
        math::vec(27, 13, 63),
        math::vec(45, 39, 61),
        math::vec(77, 33, 87)
    );
    float determinant2 = math::det(matrix2);
    float paperillaLaskettuDeterminantCaseen2 = -48208.0f;
    std::cout << "Determinante on: " << determinant2 << std::endl;
    if (determinant2 == paperillaLaskettuDeterminantCaseen2) {
        std::cout << "Case Test Determinante on: " << determinant2 << std::endl;
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Determinante NOT OK: " << determinant2 << std::endl;
        return -1;
    }
    std::cout << "..................................................................!" << std::endl;

    // tehtävä Transposion  matrizi 3x3
    // 
     // Define the original matrix
    math::mat3 originalMatrix = math::mat(
        math::vec(1.0f, 2.0f, 3.0f),
        math::vec(4.0f, 5.0f, 6.0f),
        math::vec(7.0f, 8.0f, 9.0f)
    );
    // Print the original matrix
    std::cout << "Original Matrix :" << std::endl;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << originalMatrix[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Calculate the transposed matrix
    math::mat3 transposedMatrix = math::transpose(originalMatrix);
    // Print the transposed matrix before the comparison
    std::cout << std::endl;
    std::cout << "Transpose:" << std::endl;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Define the expected transposed matrix
    math::mat3 expectedTransposedMatrix = math::mat(
        math::vec(1.0f, 4.0f, 7.0f),
        math::vec(2.0f, 5.0f, 8.0f),
        math::vec(3.0f, 6.0f, 9.0f)
    );

   
    // Print the transposed matrix after the comparison (Case Test transpose is:)
    std::cout << std::endl;
    std::cout << " (Case Test tranpose on):" << std::endl;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix[row][col] << " , ";
        }
        std::cout << std::endl;
    }
     // Compare the real transposed matrix with the expected one
    if (transposedMatrix == expectedTransposedMatrix) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }

    std::cout << "..................................................................!" << std::endl;

    math::mat3 originalMatrix1 = math::mat(
        math::vec(12.0f, 23.0f, 34.0f),
        math::vec(45.0f, 56.0f, 67.0f),
        math::vec(78.0f, 89.0f, 90.0f)
    );
    // Print the original matrix
    std::cout << "Original Matrix :" << std::endl;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << originalMatrix1[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Calculate the transposed matrix
    math::mat3 transposedMatrix1 = math::transpose(originalMatrix1);
    // Print the transposed matrix before the comparison
    std::cout << std::endl;
    std::cout << "Transpose:" << std::endl;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix1[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Define the expected transposed matrix
    math::mat3 expectedTransposedMatrix1 = math::mat(
        math::vec(12.0f, 45.0f, 78.0f),
        math::vec(23.0f, 56.0f, 89.0f),
        math::vec(34.0f, 67.0f, 90.0f)
    );


    // Print the transposed matrix after the comparison (Case Test transpose is:)
    std::cout << std::endl;
    std::cout << " (Case Test tranpose on):" << std::endl;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix1[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Compare the real transposed matrix with the expected one
    if (transposedMatrix1 == expectedTransposedMatrix1) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;

    math::mat3 originalMatrix2 = math::mat(
        math::vec(22.0f, 73.0f, 04.0f),
        math::vec(95.06f, 26.50f, 17.056f),
        math::vec(38.06f, 59.006f, 40.034f)
    );
    // Print the original matrix
    std::cout << "Original Matrix :" << std::endl;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << originalMatrix2[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Calculate the transposed matrix
    math::mat3 transposedMatrix2 = math::transpose(originalMatrix2);

    // Print the transposed matrix before the comparison
    std::cout << std::endl;
    std::cout << "Transpose:" << std::endl;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix2[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Define the expected transposed matrix
    math::mat3 expectedTransposedMatrix2 = math::mat(
        math::vec(22.0f, 95.06f, 38.06f),
        math::vec(73.0f, 26.50f, 59.006f),
        math::vec(04.0f, 17.056f, 40.034f)
    );


    // Print the transposed matrix after the comparison (Case Test transpose is:)
    std::cout << std::endl;
    std::cout << "(Case Test tranpose on):" << std::endl;
   
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::cout << transposedMatrix2[row][col] << " , ";
        }
        std::cout << std::endl;
    }
    // Compare the real transposed matrix with the expected one
    if (transposedMatrix2 == expectedTransposedMatrix2) {
        std::cout << "Test PASSED!" << std::endl;
    }
    else {
        std::cout << "Test FAILED!" << std::endl;
    }
    std::cout << "..................................................................!" << std::endl;



    return 0;
}



