#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	// �������� �������� �������
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_create_postfix_with_valid_infix)
{
	// �������� �������� ������� �� ���������� ��������� ������
	ASSERT_NO_THROW(TPostfix p("3 + 4 * (2 - 1)"));
}

TEST(TPostfix, can_create_postfix_with_parenthesis)
{
	// �������� �������� ������� �� ���������� ��������� ������ � �������� ������
	ASSERT_NO_THROW(TPostfix p("(a+b)*c"));
}

TEST(TPostfix, throws_exception_for_invalid_infix)
{
	// �������� ������� ���������� ��� ������������ ��������� ������ � �������� ������
	ASSERT_ANY_THROW(TPostfix p("3 + 4 * (2 - 1"));
}

TEST(TPostfix, can_convert_to_postfix)
{
	// �������� ������������ �������������� ��������� ������ � �����������
	TPostfix p("(a+b)*c");
	EXPECT_EQ(p.GetPostfix(), "ab+c*");
}

TEST(TPostfix, can_handle_multiple_operators)
{
	// �������� ��������� ��������� � ����������� �����������
	TPostfix p("a+b-c*d/e");
	EXPECT_EQ(p.GetPostfix(), "ab+cd*e/-");
}

TEST(TPostfix, calculate_test)
{
	// �������� ���������� �������� ������������ ��������� � �������
	TPostfix p("5+2-3*4/6");
	EXPECT_EQ(p.Calculate(), 5);
}

TEST(TPostfix, throws_exception_for_division_by_zero)
{
	// �������� ������� ���������� ��� ������� �� ����
	TPostfix p("1/0");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_handle_variables)
{
	// �������� ������ � �����������
	TPostfix p("x + y");
	p.SetVariable('x', 5);
	p.SetVariable('y', 3);
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, throws_exception_for_undefined_variable)
{
	// �������� ������� ���������� ��� ������������� �������������� ����������
	TPostfix p("x + y");
	p.SetVariable('x', 5);
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_set_multiple_variables)
{
	// �������� ��������� ���������� ����������
	TPostfix p("x + y");
	map<char, double> variables = { {'x', 5}, {'y', 3} };
	p.SetVariables(variables);
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, can_handle_variables_in_complex_expression)
{
	// �������� ��������� ���������� � ������� ����������
	TPostfix p("x + y * z");
	map<char, double> variables = { {'x', 2}, {'y', 3}, {'z', 4} };
	p.SetVariables(variables);
	EXPECT_EQ(p.Calculate(), 14);
}
TEST(TPostfix, can_handle_unary_minus)
{
	// �������� ��������� �������� ������
	TPostfix postfix("-5");
	EXPECT_EQ(postfix.Calculate(), -5);
}

TEST(TPostfix, can_handle_unary_minus_with_variables)
{
	// �������� ��������� ����� ������� ��������� � ������� ������
	TPostfix postfix("-x + y");
	postfix.SetVariable('x', 3);
	postfix.SetVariable('y', 2);
	EXPECT_EQ(postfix.Calculate(), -1);
}

TEST(TPostfix, can_handle_exponentiation)
{
	// �������� ��������� ���������� � �������
	TPostfix p("2^3");
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, can_handle_negative_exponentiation)
{
	// �������� ��������� ���������� � ������������� �������
	TPostfix p("2^(-3)");
	EXPECT_NEAR(p.Calculate(), 0.125, 1e-6); // ������� ���������, ������� � 0.125
}

TEST(TPostfix, can_handle_complex_expression_and_zero_exponent)
{
	// �������� ��������� ������� ��������� � ���������� � ������� �������
	TPostfix p("(2 + 3 * 4)^0");
	EXPECT_EQ(p.Calculate(), 1);
}