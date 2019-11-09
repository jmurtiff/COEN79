//See poly.h for documentation.
// 
//	INVARIENTS for the polynimial class: 
//	1. The degree of the polynomial is in the member variable currentDegree.
//	2. All coefficients of degrees larger than the currentDegree are 0;
//	3. The coefficient for the n-th degree of a polynomial is stored in coeff[n].
//	4. The maximum degree should never be exceeded. 

#include <cassert>
#include <iostream>
#include <iomanip>
#include <climits>
#include <assert.h>
#include <cmath>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
    polynomial::polynomial(double c, unsigned int exponent)
	{
    	assert(exponent <= polynomial::MAXIMUM_DEGREE);
    	currentDegree = 0; 
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
    		coeff[i] = 0; 
    	}
    	coeff[exponent] = c; 
    }

	void polynomial::update_current_degree()
	{
		for (int i = polynomial::MAXIMUM_DEGREE; i >= 0; i--)
		{
			if(coeff[i] != 0)
			{
				currentDegree = i; 
				break;
			}
		}
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
	  	assert(exponent <= polynomial::MAXIMUM_DEGREE); 
	  	coeff[exponent] = coefficient; 
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
	{
    	assert(exponent <= polynomial::MAXIMUM_DEGREE); 
    	coeff[exponent] += amount; 
    }

    void polynomial::clear()
	{
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE+1; i++)
		{
    		coeff[i] = 0; 
    	}
    }

    polynomial polynomial::antiderivative() const
	{
    	assert(degree() < polynomial::MAXIMUM_DEGREE); 
 		polynomial temp = polynomial(0.0,0); 
    	for (int i = MAXIMUM_DEGREE; i > 0; i--)
		{
    		temp.coeff[i] = coeff[i-1]; 
    		temp.coeff[i] /= i; 
    	}
    	return temp; 
    }

    double polynomial::coefficient(unsigned int exponent) const
	{
    	if(exponent > polynomial::MAXIMUM_DEGREE)
		{
			return 0.0; 
		}
    	return coeff[exponent]; 
    }

    double polynomial::definite_integral(double x0, double x1) const
	{
    	polynomial temp = antiderivative(); 
    	double ans = temp.eval(x1) - temp.eval(x0); 
    	return ans;
    }

    unsigned int polynomial::degree() const
	{
        for (int i = polynomial::MAXIMUM_DEGREE; i >= 0; i--)
		{
			if(coeff[i] != 0)
			{
				return i; 
			}
		}
		return 0;
    }

    polynomial polynomial::derivative() const
	{
 		polynomial temp = polynomial(0.0,0); 
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
    		temp.coeff[i] = coeff[i+1]; 
    		temp.coeff[i] *= (i+1); 
    	}
    	return temp;
    }

	double polynomial::eval(double x) const
	{
    	double answer = 0;
    	for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
    		answer += coeff[i]*pow(x,i); 
    	}
    	return answer;
    }

    bool polynomial::is_zero() const
	{
        if(degree() == 0)
		{
       		return true;
		}	
       	return false;
    }

    unsigned int polynomial::next_term(unsigned int e) const
	{
    	for (int i = e+1; i <= MAXIMUM_DEGREE; i++)
		{
    		if((coeff[i] > coeff[e]) && coeff[i] != 0)
			{
				return i;
			}	
    	}
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const
	{
    	for (int i = e-1; i >= 0; i--)
		{
    		if(coeff[i] != 0)
			{
				return i;
			}
    	}
        return UINT_MAX;			
    }

    double polynomial::operator() (double x) const
	{
    	return eval(x); 
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2)
	{
     	polynomial temp = polynomial(0.0,0);
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
    		temp.coeff[i] = p1.coeff[i] + p2.coeff[i]; 
    	}	
        return temp; 
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
     	polynomial temp = polynomial(0.0,0); 
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
    		temp.coeff[i] = p1.coeff[i] - p2.coeff[i]; 
    	}	
        return temp;      	
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2)
	{
        assert((p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE); 
     	polynomial temp = polynomial(0.0,0); 
        for (int i = 0; i <= p1.degree(); i++)
		{
        	for (int j = 0; j <= p2.degree(); j++)
			{
        		temp.coeff[i+j] += p1.coeff[i]*p2.coeff[j]; 
        	}
        }
        return temp; 
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p)
	{
		int i = p.degree();
		if(i > 1)
		{
			out << p.coeff[i] << "x^" << i;
			i--;
			while(i != 1)
			{
				if(p.coeff[i] > 0)
				{
					out << " + " << p.coeff[i] << "x^" << i;
				}
				else if (p.coefficient(i) < 0)
				{
					out << " - " << abs(p.coeff[i]) << "x^" << i;
				}
				i--;
			}
			if(p.coefficient(i) > 0)
			{
				out << " + " << p.coeff[i] << "x";
			}
			else if (p.coefficient(i) < 0)
			{
				out << " - " << abs(p.coeff[i]) << "x";
			}
			i--;
			if(p.coefficient(i) > 0)
			{
				out << " + " << p.coefficient(i);
			}
			else if (p.coefficient(i) < 0)
			{
				out << " - " << abs(p.coeff[i]);
			}
		}
		else if (i == 1)
		{
			out << p.coefficient(1) << "x";
			if(p.coefficient(0) > 0)
			{
				out << " + " << p.coefficient(0);
			}
			else if (p.coefficient(0) < 0)
			{
				out << " - " << abs(p.coeff[i]);
			}
		}
		else
		{
			out << p.coefficient(0);	
		}
		return out;
	}
};
