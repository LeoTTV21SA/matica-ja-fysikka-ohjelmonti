#include <stdio.h>
#include <mikroplot/window.h>
#include <fstream>
#include <iostream>
#include <math.h>

// alkuperainaen fukion f(x) = x^3 - 1
double f(double x) {
    return pow(x, 3) - 1;
}

// Derivata fuktion f(x) = x^3 - 1
double df(double x) {
    return 3 * pow(x, 2);
}


//alkuperainaen fukion g(x) = cos(x) - x^3
double g(double x) {
    return cos(x) - pow(x, 3);
}

// Derivata fuktion g(x)
double dg(double x) {
    return -sin(x) - 3 * pow(x, 2);
}

// alkuperainen funktio f(x) = (x^4 + 11x^3 + 8x^2 + 20*x - 10) / 1000
double q(double x) {
    return (pow(x, 4) + 11 * pow(x, 3) + 8 * pow(x, 2) + 20 * x - 10) / 1000;
}
// Derivata fuktion f(x) 4*(x^3 + 33 * x^2 + 16 * x + 20) / 1000

double dq(double x) {
    return (4 * pow(x, 3) + 33 * pow(x, 2) + 16 * x + 20) / 1000;
}


// Newtonin menetelm‰ juuren etsimiseksi f(x):n avulla
double newtonMethod(double x0, double (*func)(double), double (*deriv)(double)) {
    const double tolerance = 1e-6; // "Toleranssi iterointien pys‰ytt‰miseksi"
    int maxIterations = 1000; // "Maksimi iteraatioiden m‰‰r‰"

    double x = x0;
    for (int i = 0; i < maxIterations; ++i) {
        double fx = func(x);
        double dfx = deriv(x);

        if (fabs(fx) < tolerance) {
            return x;  // "Olemme lˆyt‰neet juuren toleranssin sis‰ll‰"
        }

        x = x - fx / dfx; // "Newtonin menetelm‰n iteratiivinen kaava"
    }

    return x; // "Palautamme nykyisen x-arvon, jos haluttua toleranssia ei saavutettu"
}

int main() {
    using namespace mikroplot;
    Window window(800, 800, "Notebook 2- Tes integration");
    std::ofstream outFile("t2_submissions.md");
    auto f1 = f;
    auto g1 = g;
    auto q1 = q;

    int funcNumber = 0;
    while (false == window.shouldClose()) {
        window.setScreen(-5, 5, -5, 5);
        window.drawAxis();

        double root = 0.0; // tallena Neliˆjuuri
        double min = 0.0; // tallena min arvo

        if (funcNumber == 0) {
           root = newtonMethod(0.5, f1, df);
            printf("Root found for f(x): %f\n", root);
        }

        else if (funcNumber == 1) {
            root = newtonMethod(0.5, g1, dg);
            printf("Root found for g(x): %f\n", root);
        }
        else if (funcNumber == 2) {
            min = newtonMethod(0.0, q1, dq);
            printf("Minimum found for q(x): %f\n", min);
        }
        



        outFile << "# Tehtava " << funcNumber << std::endl;
        outFile << std::endl;
        if (funcNumber == 2) {
            outFile << "Minimi: " << min << std::endl; // n‰yt‰ min arvo
        }
     


        outFile << "Root found:" << root << std::endl;
        outFile << std::endl;
        outFile << "Kuvakaappaus alla:" << std::endl;
        outFile << std::endl;
        outFile << "![alt text](screenshot" + std::to_string(funcNumber) + ".png \"Title Text\"){width=400px height=400px}" << std::endl;
        outFile << std::endl;

        //window.drawFunction(f1, 10);
        if (funcNumber == 0) window.drawFunction(f1, 10);
        else if (funcNumber == 1) window.drawFunction(g1, 11);
        else if (funcNumber == 2) window.drawFunction(q1, 12);
        window.update();
        window.screenshot("screenshot" + std::to_string(funcNumber) + ".png");

        // Update funcNumber: 0 <= funcNumber < 4
        ++funcNumber;
        if (funcNumber >= 3) {
            funcNumber = 0;
            break;
        }
    }
   

    window.update();

    printf("End app\n");
    return 0;
}
