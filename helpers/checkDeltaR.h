// checkDeltaR.h


#ifndef CHECK_DELTA_R_H_INCL
#define CHECK_DELTA_R_H_INCL


template <typename T> 
float deltaPhi(T v1, T v2, const T c = M_PI) {
    auto r = std::fmod(v2 - v1, 2.0 * c);
    if (r < -c) {
        r += 2.0 * c;
    }
    else if (r > c) {
        r -= 2.0 * c;
    }
    return r;
}


float deltaR(float eta1, float eta2, float phi1, float phi2) {
    return sqrt(pow(eta1 - eta2, 2) + pow(deltaPhi(phi1, phi2), 2));

}

bool isLeadingDeltaRLarge(const std::vector<TLorentzVector> *v1, const std::vector<TLorentzVector> *v2, float thresholdDeltaR = 0.5) {

    if ((v1->size() > 0) && (v2->size() > 0)) {

        float eta1 = v1->at(0).Eta();
        float phi1 = v1->at(0).Phi();

        float eta2 = v2->at(0).Eta();
        float phi2 = v2->at(0).Phi();

        float deltaR = sqrt(pow(eta1 - eta2, 2) + pow(deltaPhi(phi1, phi2), 2));

        printf("for eta/phi pairs %f %f and %f %f, deltaR: %f", eta1, phi1, eta2, phi2, deltaR);

        return (deltaR > thresholdDeltaR);
    }
    else {
        printf("[WARNING:] checkLeadingDeltaR: one or both of the vectors has length zero, cannot compare elements\n");
        return false;
    }



}



#endif