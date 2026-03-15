#include "User.h"
#include <iostream>

User::User() {};
User::User(const std::string& name, int age, int id, 
	const std::string& gender,
	const std::string& phone,
	const std::string& email) 
	: _id(id),_age(age),_name(name),
	  _gender(gender), _phone(phone), _email(email) {};


void User::setName(const std::string& n) {
	_name = n;
};
std::string User::getName() const {
	return _name;
};

void User::setId(int id) {
	_id = id;
};
int User::getId() const {
	return _id;
};

void User::setAge(int age) {
	_age = age;
};
int User::getAge() const {
	return _age;
};

void User::setGender(const std::string& gender) {
	_gender = gender;
};
std::string User::getGender() const {
	return _gender;
};

void User::setPhone(const std::string& phone) {
	_phone = phone;
};
std::string User::getPhone() const {
	return _phone;
};

void User::setEmail(const std::string& email) {
	_email = email;
};
std::string User::getEmail() const {
	return _email;
};

void User::display() const {
	std::cout
		<< "ID: " << _id << "\n"
		<< "Name: " << _name << "\n"
		<< "Age: " << _age << "\n"
		<< "Gender: " << _gender << "\n"
		<< "Phone: " << _phone << "\n"
		<< "Email: " << _email << "\n";
}