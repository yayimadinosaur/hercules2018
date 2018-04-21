#!/usr/bin/python3

import smtplib
import getpass

sender = ""
receiver = ""
subject = ""
message = ""
sender_check = 0
receiver_check = 0
message_check = 0
attempt_check = 0
subject_check = 0

def confirm_choice():
    choice = input("Is that correct?\n")
    choice = choice.lower()
    if choice == 'y' or choice == 'yes':
        return 1
    return 0

def send_target():
    global sender, sender_check
    while sender_check == 0:
        sender = input("email of sender?\n")
        if sender == "":
            print("FROM field is blank")
            continue
        if "gmail.com" not in sender:
            print("this program only handles @gmail.com")
            continue
        print("FROM [%s]" % sender)
        if confirm_choice() == 1:
            sender_check = 1
        
def receive_target():
    global receiver, receiver_check
    while receiver_check == 0:
        receiver = input("email of receiver?\n")
        if receiver == "":
            print("TO Field is blank")
            continue
        print("TO[%s]" % receiver)
        if confirm_choice() == 1:
            receiver_check = 1

def email_subject():
    global email_subject, subject_check
    while subject_check == 0:
        email_subject = input("email subject\n")
        print("SUBJECT[%s]" % email_subject)
        if confirm_choice() == 1:
            subject_check = 1

def email_message():
    global message, message_check
    while message_check == 0:
        message = input("MESSAGE TO [" + receiver + "]?\n")
        print("-----\nEMAIL MESSAGE:\n-----")
        print(message + '\n-----')
        if confirm_choice() == 1:
            message_check = 1

#summary of email before sending
def email_summary():
    print("-----\nEmail Summary")
    print("[To]")
    print(sender)
    print("[From]")
    print(receiver)
    print("[Subject]")
    print(email_subject)
    print("[Email Message]")
    print(message)
    if confirm_choice() == 1:
        email_attempt()
    print("please rerun program")
    exit()

#concats sender, receiver, subject, and message
#trys to email receiver, prints errors if there are
#exits program
def email_attempt():
    global attempt_check
    final_email = """From: %s\nTo: %s\nSubject: %s\n\n%s""" % (sender, receiver, email_subject, message)
    while attempt_check == 0:
        try:
            server = smtplib.SMTP("smtp.gmail.com", 587)
            print("starting smtp server via gmail")
            server.ehlo()
            server.starttls()
            gmail_pw = getpass.getpass("Enter email pw for [%s]\n(Will be hidden)" % sender)
            server.login(sender, gmail_pw)
            #server.sendmail(sender, receiver, message)
            server.sendmail(sender, receiver, final_email)
            server.close()
            print("email is a success!\nclosing server")
        except smtplib.SMTPException as e:
            print("Error!\n[%s]" % str(e))
        attempt_check = 1
    print("Exiting Girdle")
    exit()

def main():
    send_target()
    receive_target()
    email_subject()
    email_message()
    email_summary()
    send_email()

if __name__ == "__main__":
    main()
