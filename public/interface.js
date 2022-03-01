class Lev {
    static SizeT (a) {
        return 2^a
    };

    static lookFor(pattern, text, maxDistance) {
        if (pattern.length < this.SizeT(8)) {
            return Module.lookFor8(pattern, text, maxDistance)
        }
        else if (pattern.length < this.SizeT(16)) {
            return Module.lookFor16(pattern, text, maxDistance)
        }
        else if (pattern.length < this.SizeT(32)) {
            return Module.lookFor32(pattern, text, maxDistance)
        }
        else if (pattern.length < this.SizeT(64)) {
            return Module.lookFor64(pattern, text, maxDistance)
        }
        else {
            console.error("Zbyt długi wzorzec. Maksymalna długość to ", this.SizeT(64) ," znaków.")
        }


    };
}