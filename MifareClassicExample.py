import nxppy
import time

#create an Myfare object
mifare = nxppy.Mifare()
while True:
    try:
        # get the Uid for a detected Mifare
        uid = mifare.select()
        print(uid)
        i=0
        if(uid is not None):
            #get the type of the Mifare Card as string
            #MIFARE DESFire
            #MIFARE Ultralight
            #MIFARE Mini
            #MIFARE Classic 1k
            #MIFARE Classic 4k
            #None
            MifareType=mifare.get_type()
            print(MifareType)
            #Create a Key for Classic Authentication
            key = [0xff,0xff,0xff,0xff,0xff,0xff]
            #Authenticate on the mifare classic card
            #return the card uid if the authentication was correct
            #params (block, key data, key type 0 for A type and 1 for B type
            uid = mifare.classic_authenticate(8,key,0)
            #Read a previus authenticate block, 16 bytes ins return
            #params (block to read)
            data= mifare.classic_read(8)
            print(data)
            data="Test " +str(i)
            i=i+1
            #Write on a previus authenticate block (16 bytes)
            #return 1 if the writing was correct
            #params (block index,data)
            result=mifare.classic_write(8,data)
            time.sleep(1)


    except nxppy.SelectError:
				# SelectError is raised if no card is in the field.
				pass