/////// Creation of Phi Zones used in Pattern Recognition
///////
///////
///////Takes in vector of Converted Hits from Primitive Converter function and creates a set of 4 zones 
///////which are PhiMemoryImages containing all of the hits
///////

#include "PhiMemoryImage.h"
#include "EmulatorClasses.h"


ZonesOutput zonemaker(std::vector<ConvertedHit> ConvHits){

	
	PhiMemoryImage image0;
	std::vector<PhiMemoryImage> zones (4,image0);
	

		for(std::vector<ConvertedHit>::iterator h = ConvHits.begin();h != ConvHits.end();h++){																																																														 
		
			for(int zone = 0;zone<4;zone++){
			
				for(std::vector<int>::iterator in_this_zone = h->ZoneContribution().begin();in_this_zone != h->ZoneContribution().end();in_this_zone++){
		
					if(zone == *in_this_zone)
						zones[zone].SetBit(h->Station(),(h->Zhit()+1));
				}	
			}
			
			std::cout<<"\n\nst: "<<h->Station()<<" - wire: "<<h->Wire()<<" - strip: "<<h->Strip()<<" - zzhit = "<<h->Zhit()<<" ";
			
		}
		
	ZonesOutput output;
	output.zone = zones;
	output.convertedhits = ConvHits;
	
	return output;
}


std::vector<ZonesOutput> Zones(std::vector<std::vector<ConvertedHit>> Hits){

	
	ZonesOutput tmp;
	std::vector<ZonesOutput> output (3,tmp);
	
	for(int i=0;i<3;i++)
		output[i] = zonemaker(Hits[i]);
	
	
	return output;

}
