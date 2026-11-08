#include "Casa.h"

Casa::Casa() {
}

bool Casa::EsApuestaValida(int monto) {

    return monto >= apuestaMinima &&
        monto <= apuestaMaxima &&
        monto <= dineroBanca;
}

bool Casa::intentarPagarPremio(int monto) {

    if (monto <= 0 || monto > dineroBanca) {
        return false;
    }

    dineroBanca -= monto;
    return true;
}

void Casa::recibirApuestaPerdida(int monto) {

    if (monto > 0) {
        dineroBanca += monto;
    }
}

int Casa::getDineroBanca() {

    return dineroBanca;
}