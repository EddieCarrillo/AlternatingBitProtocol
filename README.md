# AlternatingBitProtocol
Implements Alternating Bit Protocol as a Reliable Trasport Protocol (Lab)



High Level Algorithm:

# Sender Side

# 0 case
If state == Wait-For-Call-0-From-Above #If we are not waiting for an ACK and are waiting for data to be passed in from Application Layer
   If event == rdt_rcv(rcvpkt) //then ignore the packet (since we are not anticipating an ACK)
   Else if event == rdt_send(data) //The application layer has some data to send.
       Take the packet.
       Calculate the checksum
       Create the segment
       Send the segment into the network layer
       Transition to Wait-For-Ack-0 state.
       Start the timer //To approximate/guess packet loss 
If state == Wait-For-Ack-0 //We have transmitted a packet with seq_num == 0, thus we are waiting for an ACK 0 from the reciever.
    If event == rdt_rcv(rcvpkt) AND (isCorrupt(rcvpkt) OR isACK(rcvPacket,1)) //If we have received a packet, and it is corrupt or an ACK for the wrong seq number
        Do nothing
    If event == timeout
        Retransmit the packet
        Start the Timer
    If event == rdt_rcv(rcvpkt) AND (notCorrupt(rcvpkt) AND isACK(rcvpkt,0)) //If we have received a packet, it is not corrupt and the ACK number is correct.
        Stop the Timer //At this point we are just anticipating data from the upper layer, thus the timer is not neccesary
        Transition to Wait-From-Call-1-From-Above state.

# 1 case
This case logic is symmetric with respect to the zero case, therefore I will not repeat it here.

#Receiver        

#0 Case

If state == Wait-For-0-From-Below
    if event == rdt_rcv(rcvpkt) AND (isCorrupt(rcvpkt) OR has_seq1(rcvpkt) //If we have received a packet and it is corrupt or it has the wrong seq number
        Compute the checksum 
        Create the packet/segment
        Send the packet with ACK 1
    else if event == rdt_rcv(rcvpkt) AND notCorrupt(rcvpkt) AND has_seq0(rcvpkt)
        Extract(rckpkt, data)
        Deliver_data(data)
        Compute the checksum 
        Crete the packet/segment
        Send the packet to the network layer with Ack_num header field value of 0
        Transition to Wait-For-1-From-Below


