// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0;

// Polymorphism of function with same name but different parameter type.
contract A {

    function poly(uint16 b) public pure returns (uint16) {
        return b;
    }

    function poly(int8 a) public pure returns (int8) {
        return a;
    }
}

contract C {
    function test_poly() public {
        A contract_A = new A();
        assert(contract_A.poly(-2) == -2);
        assert(contract_A.poly(300) == 300);
    }
}