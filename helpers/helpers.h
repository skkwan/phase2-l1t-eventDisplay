// helpers.h

#ifndef HELPERS_H_INCL
#define HELPERS_H_INCL

static bool comparePt(const TLorentzVector& lhs, const TLorentzVector& rhs) {
    return ( lhs.Pt() > rhs.Pt() );
}

#endif